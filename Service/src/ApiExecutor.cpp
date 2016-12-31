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
#include "Session.h"
#include "SessionManager.h"
#include "AppException.h"
#include "LogInHelper.h"
#include "InternalRootRequester.h"

#include <cpprest/http_headers.h>


namespace Rest {

web::json::value ApiExecutor::ExecuteSingleApi(const web::http::http_request& request,
        const web::json::value &jrequest)
{
    web::json::value jresponse;
    const web::json::value &japi = jrequest.at(JSON_API);
    const web::json::value &jdata = jrequest.at(JSON_DATA);
    std::string apiName = utility::conversions::to_utf8string(japi.as_string());

    if (japi.is_string() && jdata.is_object()) {

        std::shared_ptr<Api::Serializable> obj = Api::SOFactory::CreateObject(apiName);
        if (obj) {

            if (apiName.compare("login") != 0) {

                const web::http::http_headers &headers = request.headers();
                bool hasToken = headers.has(U("Auth-Token"));

                if (hasToken) {

                    auto itr = headers.find(U("Auth-Token"));
                    utility::string_t token_t = itr->second;
                    std::string token = utility::conversions::to_utf8string(token_t);

                    bool validToken = Dal::SessionManager::IsValidToken(token);

                    if (validToken) {

                        std::shared_ptr<Api::BaseInput> input =
                                std::dynamic_pointer_cast<Api::BaseInput, Api::Serializable>(obj);

                        if (input) {
                            //prepare input
                            input->Deserialize(jdata);

                            try {
                                Dal::SessionManager::SetPinned(token, true);
                                Dal::SessionManager::ResetExpiration(token);
                                Dal::Requester *requester = Dal::SessionManager::GetRequetser(token);

                                std::shared_ptr<Api::BaseOutput> output = input->Process(requester);

                                if (output->GetError().GetCode() == AppErrorCode::SUCCESS) {
                                    //execute api
                                    jresponse = output->GetResponse();
                                } else {
                                    //jresponse = output->GetErrorResponse();
                                    //LOG_ERROR("API: " + apiName + " failed with error [" + jresponse.serialize() + "]");
                                }

                                Dal::SessionManager::SetPinned(token, false);

                            } catch (Common::AppException &e) {
                                Dal::SessionManager::SetPinned(token, false);
                                jresponse = e.Serialize();
                                LOG_ERROR("API: " + apiName + " failed with error [" + jresponse.serialize() + "]");
                                return jresponse;

                            } catch (std::exception &e) {
                                Dal::SessionManager::SetPinned(token, false);
                                Common::AppException ex = Common::AppException(e);
                                jresponse = ex.Serialize();
                                LOG_ERROR("API: " + apiName + " failed with error [" + jresponse.serialize() + "]");
                                return jresponse;
                            }
                        } else {
                            jresponse = Api::ApiUtils::ErrorResponse(AppErrorCode::INTERNAL_SERVER_ERROR,
                                    "Could not cast shared pointer of Serializable to BaseInput");
                            LOG_ERROR("API: " + apiName + " failed with error [" + jresponse.serialize() + "]");
                            return jresponse;
                        }
                    } else {
                        jresponse = Api::ApiUtils::ErrorResponse(AppErrorCode::UNAUTHORIZED,
                                "Unauthorized request");
                        LOG_ERROR("API: " + apiName + " failed with error [" + jresponse.serialize() + "]");
                        return jresponse;
                    }
                } else {
                    jresponse = Api::ApiUtils::BadRequestResponse();
                    LOG_ERROR("API: " + apiName + " failed with error [" + jresponse.serialize() + "]");
                    return jresponse;
                }
            } else {
                std::shared_ptr<Api::BaseInput> input =
                        std::dynamic_pointer_cast<Api::BaseInput, Api::Serializable>(obj);

                if (input) {

                    Api::LogInHelper helper(Dal::InternalRootRequester::GetInstance(),
                            dynamic_cast<Api::LogInInput*> (&(*input)));

                    std::shared_ptr<Api::LogInOutput> output =
                            std::dynamic_pointer_cast<Api::LogInOutput, Api::BaseOutput>(helper.Execute());

                    if (output->GetError().GetCode() == AppErrorCode::SUCCESS) {
                        
                        jresponse = output->GetResponse();
                        
                        Api::SessionManager::AddSession(output->GetSessionToken(),
                                output->GetUser(), output->GetSessionExpires());
                    } else {
                        //jresponse = output->GetErrorResponse();
                        //LOG_ERROR("API: " + apiName + " failed with error [" + jresponse.serialize() + "]");
                    }
                } else {
                    return Api::ApiUtils::ErrorResponse(AppErrorCode::INTERNAL_SERVER_ERROR,
                            "Could not cast shared pointer of Serializable to BaseInput");
                }
            }

        } else {
            return Api::ApiUtils::BadRequestResponse();
        }
    } else {
        return Api::ApiUtils::BadRequestResponse();
    }

    return jresponse;
}

web::json::value ApiExecutor::ExecuteMultipleApi(const web::http::http_request& request, const web::json::value &jrequests)
{
    web::json::value responses = web::json::value::array();
    int index = 0;
    for (auto &jrequest : jrequests.as_array()) {
        responses[index++] = ExecuteSingleApi(request, jrequest);
    }
    return responses;
}


} //namespace Server
