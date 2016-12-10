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
#include "SOFactory.h"
#include "RegisterUserInput.h"
#include "RegisterUserOutput.h"
#include "ServiceFacade.h"
#include "AppFactory.h"
#include "ApiUtils.h"



namespace Server {

web::json::value ApiExecutor::ExecuteSingleApi(const web::json::value &jrequest)
{
    web::json::value jresponse;
    const web::json::value &japi = jrequest.at(JSON_API);
    const web::json::value &jdata = jrequest.at(JSON_DATA);
    std::string apiName = utility::conversions::to_utf8string(japi.as_string());

    if (japi.is_string() && jdata.is_object()) {
        std::shared_ptr<Api::Serializable> obj = std::move(Api::SOFactory::CreateObject(std::move(apiName)));
        if (obj) {
            std::shared_ptr<Api::BaseInput> input = std::dynamic_pointer_cast<Api::BaseInput, Api::Serializable>(obj);

            if (input) {
                input->Deserialize(jdata);

                jresponse = input->Process();
            } else {
                return Api::ApiUtils::ErrorResponse(AppErrorCode::INTERNAL_SERVER_ERROR,
                                                    "Could not cast shared pointer of Serializable to BaseInput");
            }
        } else {
            return Api::ApiUtils::BadRequestResponse();
        }
    } else {
        return Api::ApiUtils::BadRequestResponse();
    }

    return jresponse;
}

web::json::value ApiExecutor::ExecuteMultipleApi(const web::json::value &jrequests)
{
    web::json::value responses = web::json::value::array();
    int index = 0;
    for(auto &request : jrequests.as_array()) {
        responses[index++] = ExecuteSingleApi(request);
    }
    return responses;
}


} //namespace Server
