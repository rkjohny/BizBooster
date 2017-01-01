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
    const web::json::value &japi = jrequest.at(JSON_API);
    const web::json::value &jdata = jrequest.at(JSON_DATA);
    std::string apiName = utility::conversions::to_utf8string(japi.as_string());

    Api::ApiError error(AppErrorCode::SUCCESS, "Success");

    if (japi.is_string() && jdata.is_object()) {

        std::shared_ptr<Api::Serializable> obj = Api::SOFactory::CreateObject(apiName);
        if (obj) {

            if (apiName.compare("login") == 0) {
                std::shared_ptr<Api::LogInInput> input =
                        std::dynamic_pointer_cast<Api::LogInInput, Api::Serializable>(obj);

                if (input) {
                    Api::LogInHelper helper(Dal::InternalRootRequester::GetInstance(), input.get());

                    std::shared_ptr<Api::LogInOutput> output =
                            std::dynamic_pointer_cast<Api::LogInOutput, Api::BaseOutput>(helper.Execute());

                    if (output->GetError().GetCode() == AppErrorCode::SUCCESS) {

                        jresponse = output->GetResponse();

                        Api::AppSessionManager::AddSession(output->GetSessionToken(),
                                output->GetUser(), output->GetSessionExpires());
                    } else {
                        error = output->GetError();
                    }
                } else {
                    error.SetError(AppErrorCode::INTERNAL_SERVER_ERROR,
                            "Could not cast shared pointer of Serializable to BaseInput");
                }
            } else if (apiName.compare("loggedin") == 0) {
                std::shared_ptr<Api::LoggedInInput> input =
                        std::dynamic_pointer_cast<Api::LoggedInInput, Api::Serializable>(obj);

                if (input) {
                    Api::LoggedInHelper helper(Dal::InternalRootRequester::GetInstance(), input.get());

                    std::shared_ptr<Api::LoggedInOutput> output =
                            std::dynamic_pointer_cast<Api::LoggedInOutput, Api::BaseOutput>(helper.Execute());

                    if (output->GetError().GetCode() == AppErrorCode::SUCCESS) {

                        jresponse = output->GetResponse();

                        Api::AppSessionManager::AddSession(input->GetSessionToken(), output->GetUser(), input->GetSessionExpires());
                    } else {
                        error = output->GetError();
                    }
                } else {
                    error.SetError(AppErrorCode::INTERNAL_SERVER_ERROR,
                            "Could not cast shared pointer of Serializable to BaseInput");
                }
            } else {
                const web::http::http_headers &headers = request.headers();
                bool hasToken = headers.has(U("Auth-Token"));

                if (hasToken) {

                    auto itr = headers.find(U("Auth-Token"));
                    utility::string_t token_t = itr->second;
                    std::string token = utility::conversions::to_utf8string(token_t);

                    bool validToken = Api::AppSessionManager::IsValidToken(token);

                    if (validToken) {

                        std::shared_ptr<Api::BaseInput> input =
                                std::dynamic_pointer_cast<Api::BaseInput, Api::Serializable>(obj);

                        if (input) {
                            //prepare input
                            input->Deserialize(jdata);

                            try {
                                auto session = Api::AppSessionManager::GetSession(token).lock();
                                if (session && !session->IsExpired()) {
                                    session->ResetExpiration();
                                    auto requester = session->GetRequester().lock();
                                    if (requester) {
                                        std::shared_ptr<Api::BaseOutput> output = input->Process(requester.get());

                                        if (output->GetError().GetCode() == AppErrorCode::SUCCESS) {
                                            jresponse = output->GetResponse();
                                        } else {
                                            error = output->GetError();
                                        }
                                    } else {
                                        error.SetError(AppErrorCode::UNAUTHORIZED, "Unauthorized request");
                                    }
                                } else {
                                    error.SetError(AppErrorCode::UNAUTHORIZED, "Unauthorized request");
                                }
                            } catch (Common::AppException &e) {
                                error.SetError(e);
                            } catch (std::exception &e) {
                                error.SetError(e);
                            }
                        } else {
                            error.SetError(AppErrorCode::INTERNAL_SERVER_ERROR,
                                    "Could not cast shared pointer of Serializable to BaseInput");
                        }
                    } else {
                        error.SetError(AppErrorCode::UNAUTHORIZED, "Unauthorized request");
                    }
                } else {
                    error.SetError(AppErrorCode::BAD_REQUEST, "Bad request");
                }
            }

            if (error.GetCode() != AppErrorCode::SUCCESS) {
                jresponse = error.Serialize();
                LOG_ERROR("API: " + apiName + " failed with error [" + jresponse.serialize() + "]");
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
