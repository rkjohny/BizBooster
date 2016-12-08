/*
 * Copyright (C) 20016 Rezaul Karim (rkjohny@gmail.com)
 *     The information contained here-in is the property of the author (Rezaul Karim)
 *     and is not to be disclosed or used without prior written permission of the author.
 *     This copyrightextends to all media in which this information may be preserved
 *     including magnetic storage, computer print-out or visual display.
 */

#include "ApiExecutor.h"
#include "SOFactory.h"
#include "RegisterUserInput.h"
#include "RegisterUserOutput.h"
#include <Converter.h>
#include <ServiceFacade.h>
#include "AppFactory.h"

namespace Server {

web::json::value ApiExecutor::UnknownErrorResponse()
{
    web::json::value jresponse;
    jresponse[U("error")] = web::json::value::number(Api::ApiReturnCode::UN_KNOWN_ERROR);
    jresponse[U("message")] = web::json::value::string(U(UN_KNOWN_ERROR_STR));
    return jresponse;
}

web::json::value ApiExecutor::BadRequestResponse()
{
    web::json::value jresponse;
    jresponse[U("error")] = web::json::value::number(Api::ApiReturnCode::BAD_REQUEST);
    jresponse[U("message")] = web::json::value::string(U(BAD_REQUEST_STR));
    return jresponse;
}

web::json::value ApiExecutor::InternalServerErrorResponse()
{
    web::json::value jresponse;
    jresponse[U("error")] = web::json::value::number(Api::ApiReturnCode::INTERNAL_SERVER_ERROR);
    jresponse[U("message")] = web::json::value::string(U(INTERNAL_SERVER_ERROR_STR));
    return jresponse;
}


web::json::value ApiExecutor::ExecuteSingleApi(const web::json::value &jrequest)
{
    web::json::value jresponse;
    const web::json::value &japi = jrequest.at(JSON_API);
    const web::json::value &jdata = jrequest.at(JSON_DATA);
    std::string apiName = utility::conversions::to_utf8string(japi.as_string());

    if (japi.is_string() && jdata.is_object()) {
        std::unique_ptr<Api::Serializable> obj =  Api::SOFactory::CreateObject(std::move(apiName));
        if (obj) {
            std::unique_ptr<Api::BaseInput> input =
                    Common::Converter::DynamicDownCast<Api::BaseInput, Api::Serializable>(std::move(obj));

            input->Deserialize(jdata);

            LOG_DEBUG("Input: " + input->Serialize().serialize());

            jresponse = input->Process();

        } else {
            return BadRequestResponse();
        }
    } else {
        return BadRequestResponse();
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
