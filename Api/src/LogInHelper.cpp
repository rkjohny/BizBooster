/**
 * Author: Rezaul Karim
 * Email: rkjohny@gmail.com
 *
 * Copyright (C) 20016 Rezaul Karim (rkjohny@gmail.com) all rights reserved.
 *
 * The information contained here-in is the property of Rezaul Karim and is not to be
 * disclosed or used without prior written permission of Rezaul Karim. This copyright
 * extends to all media in which this information may be preserved including
 * magnetic storage, computer print-out or visual display.
 */

#include "LogInHelper.h"
#include "Dal.h"
#include "LCrypto.h"
#include "DateTimeUtils.h"
#include "ApiDef.h"
#include "CryptoDef.h"
#include "Roles.h"


namespace Api {

void LogInHelper::InitAndValidate()
{
    m_user = Dal::GetDao()->GetUser(m_requester, m_input->GetUserName());
    if (!m_user) {
        throw Common::AppException(AppErrorCode::AUTHTICATION_FAILURE, "Invalid username password.");
    }
    m_authInfo = m_user->GetAuthInfo();
}

void LogInHelper::CheckPermission()
{
    if (!m_requester->HasRole(Dal::Role::ROLE_INTERNAL_ROOT_USER)) {
        throw Common::AppException(AppErrorCode::INTERNAL_SERVER_ERROR, "Invalid request");
    }
}

void LogInHelper::ExecuteHelper()
{
    m_authInfo = m_user->GetAuthInfo();
    auto authInfo = m_authInfo.lock();

    if (authInfo) {
        if (m_input->IsUseFacebookAuth()) {
            throw Common::AppException(AppErrorCode::NOT_SUPPORTED, "Google authentication is not supported yet");
        } else if (m_input->IsUseFacebookAuth()) {
            throw Common::AppException(AppErrorCode::NOT_SUPPORTED, "Facebook authentication is not supported yet");
        } else {
            std::string passHash = authInfo->passwordHash();
            std::string passSalt = authInfo->passwordSalt();
            std::string passMethod = authInfo->passwordMethod();

            auto hasFun = LCrypto::GetHashGenerator();
            bool valid = false;

            if (passMethod.compare(HASH_METHOD_BCRYPT) == 0) {
                valid = hasFun->Verify(LCrypto::HashGenerator::HashMethod::BCRYPT, m_input->GetPassword(), passHash, passSalt);
            } else if (passMethod.compare(HASH_METHOD_SHA1) == 0) {
                valid = hasFun->Verify(LCrypto::HashGenerator::HashMethod::SHA1, m_input->GetPassword(), passHash, passSalt);
            }

            if (!valid) {
                throw Common::AppException(AppErrorCode::AUTHTICATION_FAILURE, "Invalid username password.");
            }
            Wt::WDateTime now = Common::DateTimeUtils::Now();
            Wt::WDateTime expires = Common::DateTimeUtils::AfterMSec(DEFAULT_SESSION_TIME_OUT_IN_MSC);

            std::string authToken;
            LCrypto::GetRndGenerator()->GetRandomBytes(authToken, AUTH_TOKEN_LENGTH);
            //auto authTokenObj = new Wt::Dbo::ptr<Dal::AuthInfo::AuthTokenType>(authToken, expires);
            //auto at = new Wt::Auth::Dbo::AuthToken<Wt::Auth::Dbo::AuthInfo<Dal::User>>(authToken, expires);

            auto authTokenObj = new Dal::AuthToken(authToken, expires);

            auto mod_authInfo = authInfo.modify();
            mod_authInfo->setLastLoginAttempt(now);
            mod_authInfo->authTokens().insert(authTokenObj);

            m_output->SetSessionToken(authToken);
        }
    } else {
        throw Common::AppException(AppErrorCode::AUTHTICATION_FAILURE, "Invalid username password.");
    }

}

}