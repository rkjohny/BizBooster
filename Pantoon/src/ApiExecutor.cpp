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


#include "ApiExecutor.h"
#include "AppCommonDef.h"
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


namespace Pantoon {

web::json::value ApiExecutor::ExecuteSingleApi(const web::http::http_request& request,
        const web::json::value &jrequest)
{
    web::json::value jresponse;
    const auto &japi = jrequest.at(JSON_API);
    const auto &jdata = jrequest.at(JSON_DATA);
    const auto apiName = utility::conversions::to_utf8string(japi.as_string());
    
    Mocxygen::ApiError error(AppErrorCode::SUCCESS, "Success");

    if (japi.is_string() && jdata.is_object()) {

        auto obj = Mocxygen::SOFactory::CreateObject(apiName);
        if (obj) {
            Cruxdb::Requester *requester = nullptr;
            std::shared_ptr<Cruxdb::Requester> requesterPtr = nullptr;
            std::shared_ptr<Mocxygen::AppSession> session = nullptr;
            auto extendExpiration = false;

            if (apiName.compare("login") == 0) {
                requester = Cruxdb::InternalRootRequester::GetInstance();
            } else if (apiName.compare("loggedin") == 0) {
                requester = Cruxdb::InternalRootRequester::GetInstance();
            } else {
                auto &headers = request.headers();
                bool hasToken = headers.has(U("Auth-Token"));
                bool validToken = false;
                std::string token = "";
                if (hasToken) {
                    auto itr = headers.find(U("Auth-Token"));
                    token = utility::conversions::to_utf8string(itr->second);
                    validToken = Mocxygen::AppSessionManager::IsValidToken(token);
                }
                if (validToken) {
                    extendExpiration = true;
                    session = Mocxygen::AppSessionManager::GetSession(token).lock();
                    if (session && !session->IsExpired()) {
                        requesterPtr = session->GetRequester().lock();
                        if (requesterPtr) {
                            requester = requesterPtr.get();
                        }
                    }
                }
            }

            if (requester) {
                auto input = std::dynamic_pointer_cast<Mocxygen::BaseInput, Mocxygen::Serializable>(obj);
                
                input->Deserialize(jdata);
                auto output = input->Process(requester);
                
                if (output->GetError().GetCode() == AppErrorCode::SUCCESS) {
                    jresponse = output->SerializedValue();
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
