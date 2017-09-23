/**
 * Author: Rezaul Karim
 * Email: rkjohny@gmail.com
 *
 * Copyright (C) 2017 Rezaul Karim (rkjohny@gmail.com) all rights reserved.
 *
 * The information contained here-in is the property of Rezaul Karim and is not to be
 * disclosed or used without prior written permission of Rezaul Karim. This copyright
 * extends to all media in which this information may be preserved including
 * magnetic storage, computer print-out or visual display.
 */

#include "LoginHelper.h"
#include "LibCruxdb.h"
#include "LibCipher.h"
#include "DateTimeUtils.h"
#include "MocxygenDef.h"
#include "CipherDef.h"
#include "Roles.h"
#include "AppSessionManager.h"
#include "CruxdbDef.h"

namespace Mocxygen {


    void LoginHelper::ExecuteHelper() noexcept(false) {
        if (!m_requester->HasRole(Cruxdb::Role::ROLE_INTERNAL_ROOT_USER)) {
            throw Common::AppException(AppErrorCode::INTERNAL_SERVER_ERROR, "Invalid requester");
        }

        if (m_input->GetUserName()) {
            m_user = Cruxdb::GetUserService()->GetUser(m_requester, *m_input->GetUserName());
            if (!m_user) {
                throw Common::AppException(AppErrorCode::AUTHTICATION_FAILURE, "Invalid username password.");
            }
            auto &authInfo = m_user->GetAuthInfo();
            m_authInfo = authInfo.lock();

            if (!m_authInfo) {
                throw Common::AppException(AppErrorCode::AUTHTICATION_FAILURE, "Invalid username password.");
            }

            if (m_input->IsUseFacebookAuth()) {
                throw Common::AppException(AppErrorCode::NOT_SUPPORTED, "Google authentication is not supported yet");
            } else if (m_input->IsUseFacebookAuth()) {
                throw Common::AppException(AppErrorCode::NOT_SUPPORTED, "Facebook authentication is not supported yet");
            } else {
                auto &passHash = m_authInfo->passwordHash();
                auto &passSalt = m_authInfo->passwordSalt();
                auto &passMethod = m_authInfo->passwordMethod();

                auto hasFun = Cipher::GetHashGenerator();
                bool valid = false;

                if (m_input->GetPassword()) {
                    if (passMethod.compare(HASH_METHOD_BCRYPT) == 0) {
                        valid = hasFun->Verify(Cipher::HashGenerator::HashMethod::BCRYPT, *m_input->GetPassword(),
                                               passHash,
                                               passSalt);

                    } else if (passMethod.compare(HASH_METHOD_SHA1) == 0) {
                        valid = hasFun->Verify(Cipher::HashGenerator::HashMethod::SHA1, *m_input->GetPassword(),
                                               passHash,
                                               passSalt);
                    }
                }

                if (!valid) {
                    throw Common::AppException(AppErrorCode::AUTHTICATION_FAILURE, "Invalid username password.");
                }
                auto now = Common::DateTimeUtils::Now();
                auto expires = Common::DateTimeUtils::AddSecToNow(DEFAULT_SESSION_TIME_OUT_IN_SEC);

                std::string authToken;
                Cipher::GetRndGenerator()->GetRandomBytes(authToken, AUTH_TOKEN_LENGTH);
                //auto authTokenObj = new Wt::Cruxdb::ptr<Cruxdb::AuthInfo::AuthTokenType>(authToken, expires);
                auto authTokenObj = Wt::Dbo::make_ptr<Cruxdb::AuthTokenType>(authToken, expires);

                m_authInfo.modify()->setLastLoginAttempt(now);
                m_authInfo.modify()->authTokens().insert(authTokenObj);

                m_output->SetSessionToken(authToken);
                m_output->SetSessionExpires(static_cast<uint64_t> (expires.toTime_t()));
                m_output->SetEntity(m_user);

                Mocxygen::AppSessionManager::AddSession(authToken, m_user, static_cast<uint64_t> (expires.toTime_t()));
            }
        }
    }
}