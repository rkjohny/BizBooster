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

#include "WtAuthServices.h"
#include "Converter.h"
#include "CruxdbDef.h"
#include "CipherDef.h"
#include <Wt/Auth/PasswordVerifier.h>
#include <Wt/Auth/PasswordStrengthValidator.h>
#include <Wt/Auth/HashFunction.h>
#include <Wt/Auth/Identity.h>
#include "Wt/Auth/GoogleService.h"
#include "Wt/Auth/FacebookService.h"

namespace BizBooster {

    bool WtAuthServices::m_authServiceConfigured = false;
    Wt::Auth::AuthService WtAuthServices::m_wtAuthService;
    Wt::Auth::PasswordService WtAuthServices::m_wtPasswordService(WtAuthServices::m_wtAuthService);

    std::vector<const Wt::Auth::OAuthService*> WtAuthServices::m_oauthServices;

    std::unique_ptr<Wt::Auth::OAuthService> WtAuthServices::m_wtGoogleOAuthServices;
    std::unique_ptr<Wt::Auth::OAuthProcess> WtAuthServices::m_wtGoogleOAuthProcesses;

    std::unique_ptr<Wt::Auth::OAuthService> WtAuthServices::m_wtFacebookOAuthServices;
    std::unique_ptr<Wt::Auth::OAuthProcess> WtAuthServices::m_wtFacebookOAuthProcesses;

    Wt::Auth::AuthService &WtAuthServices::GetWtAuthService() {
        return m_wtAuthService;
    }

    Wt::Auth::PasswordService &WtAuthServices::GetWtPasswordService() {
        return m_wtPasswordService;
    }

    void WtAuthServices::ConfigureAuthService() {
        if (!m_authServiceConfigured) {
            m_wtAuthService.setAuthTokensEnabled(true, "logincookie");
            m_wtAuthService.setEmailVerificationEnabled(true);
            m_wtAuthService.setEmailVerificationRequired(true);
            m_wtAuthService.setIdentityPolicy(Wt::Auth::IdentityPolicy::EmailAddress);
            m_wtAuthService.setTokenHashFunction(new Wt::Auth::BCryptHashFunction(BCRYPT_HASH_NUMBER_OF_ITERATION));
            m_wtAuthService.setRandomTokenLength(RANDOM_TOKEN_LENGTH);
            m_wtAuthService.setAuthTokenValidity(DEFAULT_TOKEN_TIME_OUT_IN_MINUTES);
            m_wtAuthService.setEmailTokenValidity(DEFAULT_TOKEN_TIME_OUT_IN_MINUTES);

            std::unique_ptr<Wt::Auth::PasswordVerifier> verifier = std::make_unique<Wt::Auth::PasswordVerifier>();
            verifier.get()->addHashFunction(std::make_unique<Wt::Auth::BCryptHashFunction>( ));
            m_wtPasswordService.setVerifier(
                    Common::Converter::DynamicUpCast<Wt::Auth::PasswordVerifier, Wt::Auth::PasswordService::AbstractVerifier>(
                            std::move(verifier)));
            m_wtPasswordService.setAttemptThrottlingEnabled(true);
            //m_wtPasswordService.setStrengthValidator(std::make_unique<Wt::Auth::PasswordStrengthValidator>());


            if (Wt::Auth::GoogleService::configured()) {
                m_wtGoogleOAuthServices = std::make_unique<Wt::Auth::GoogleService>(m_wtAuthService);
                std::string googleOAuthRedirectEndPoint = m_wtGoogleOAuthServices.get()->generateRedirectEndpoint();
                m_wtGoogleOAuthProcesses = m_wtGoogleOAuthServices.get()->createProcess(m_wtGoogleOAuthServices.get()->authenticationScope());
            } else {
                BOOST_ASSERT_MSG(false, "Google oauth service is not configured.");
            }

            if (Wt::Auth::FacebookService::configured()) {
                m_wtFacebookOAuthServices = std::make_unique<Wt::Auth::FacebookService>(m_wtAuthService);
                std::string facebookOAuthRedirectEndPoint = m_wtFacebookOAuthServices.get()->generateRedirectEndpoint();
                m_wtFacebookOAuthProcesses = m_wtFacebookOAuthServices.get()->createProcess(m_wtFacebookOAuthServices.get()->authenticationScope());
            } else {
                BOOST_ASSERT_MSG(false, "Facebook oauth service is not configured.");
            }

            m_oauthServices.push_back(m_wtGoogleOAuthServices.get());
            m_oauthServices.push_back(m_wtFacebookOAuthServices.get());

            m_authServiceConfigured = true;
        }
    }

    std::unique_ptr<Wt::Auth::OAuthService>::pointer WtAuthServices::GetWtGoogleOauthService() {
        return m_wtGoogleOAuthServices.get();
    }

    std::unique_ptr<Wt::Auth::OAuthProcess>::pointer WtAuthServices::GetWtGoogleOauthProcess() {
        return m_wtGoogleOAuthProcesses.get();
    }

    const std::vector<const Wt::Auth::OAuthService*> &WtAuthServices::GetOauthServices() {
        return m_oauthServices;
    }
}
