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


#include "ApiExecutor.h"
#include "AppDef.h"
#include "SOFactory.h"
#include "RegisterUserInput.h"
#include "RegisterUserOutput.h"
#include "ServiceFacade.h"
#include "ApiUtils.h"
#include "AppSession.h"
#include "AppSessionManager.h"
#include "AppException.h"
#include "LogInHelper.h"
#include "LoggedInHelper.h"
#include "InternalRootRequester.h"

#include <cpprest/http_headers.h>


namespace Rest {

web::json::value ApiExecutor::ExecuteSingleApi(const web::http::http_request& request,
        const web::json::value &jrequest)
{
    web::json::value jresponse;
    auto japi = jrequest.at(JSON_API);
    auto jdata = jrequest.at(JSON_DATA);
    auto apiName = utility::conversions::to_utf8string(japi.as_string());
    
    Api::ApiError error(AppErrorCode::SUCCESS, "Success");

    if (japi.is_string() && jdata.is_object()) {

        auto obj = Api::SOFactory::CreateObject(apiName);
        if (obj) {

            Dal::Requester *requester = nullptr;
            std::shared_ptr<Dal::Requester> requesterPtr = nullptr;
            std::shared_ptr<Api::AppSession> session = nullptr;
            auto extendExpiration = false;

            if (apiName.compare("login") == 0) {
                requester = Dal::InternalRootRequester::GetInstance();
            } else if (apiName.compare("loggedin") == 0) {
                requester = Dal::InternalRootRequester::GetInstance();
            } else {
                auto headers = request.headers();
                auto hasToken = headers.has(U("Auth-Token"));
                auto validToken = false;
                std::string token = "";
                if (hasToken) {
                    auto itr = headers.find(U("Auth-Token"));
                    auto token_t = itr->second;
                    token = utility::conversions::to_utf8string(token_t);
                    validToken = Api::AppSessionManager::IsValidToken(token);
                }
                if (validToken) {
                    extendExpiration = true;
                    session = Api::AppSessionManager::GetSession(token).lock();
                    if (session && !session->IsExpired()) {
                        requesterPtr = session->GetRequester().lock();
                        if (requesterPtr) {
                            requester = requesterPtr.get();
                        }
                    }
                }
            }

            if (requester) {
                auto input = std::dynamic_pointer_cast<Api::BaseInput, Api::Serializable>(obj);
                
                input->Deserialize(jdata);
                auto output = input->Process(requester);
                
                if (output->GetError().GetCode() == AppErrorCode::SUCCESS) {
                    if (extendExpiration) {
                        session->ExtendExpiration();
                    }
                } else {
                    error.SetError(output->GetError());
                }
            } else {
                error.SetError(AppErrorCode::UNAUTHORIZED, "Unauthorized requester.");
            }
        } else {
            error.SetError(AppErrorCode::BAD_REQUEST, "Bad request.");
        }
    } else {
        error.SetError(AppErrorCode::BAD_REQUEST, "Bad request.");
    }

    if (error.GetCode() != AppErrorCode::SUCCESS) {
        jresponse = error.Serialize();
        LOG_ERROR("API: " + apiName + " failed with error [" + jresponse.serialize() + "]");
    }

    return jresponse;
}

web::json::value ApiExecutor::ExecuteMultipleApi(const web::http::http_request& request, const web::json::value &jrequests)
{
    auto responses = web::json::value::array();
    int index = 0;
    for (auto &jrequest : jrequests.as_array()) {
        responses[index++] = ExecuteSingleApi(request, jrequest);
    }
    return responses;
}


} //namespace Server
