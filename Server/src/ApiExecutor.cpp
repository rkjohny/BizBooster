/*
 * Copyright (C) 20016 Rezaul Karim (rkjohny@gmail.com)
 *     The information contained here-in is the property of the author (Rezaul Karim)
 *     and is not to be disclosed or used without prior written permission of the author.
 *     This copyrightextends to all media in which this information may be preserved
 *     including magnetic storage, computer print-out or visual display.
 */

#include <ApiExecutor.h>
#include "AppConstant.h"
#include "SObjectFactory.h"
#include "Serializeable.h"
#include "BaseInput.h"
#include "BaseOutput.h"

#include "Json.h"
#include <string>
#include <cpprest/asyncrt_utils.h>
#include <cpprest/json.h>


using namespace Server;
using namespace web;

web::json::value ApiExecutor::ExecuteSingleApi(const web::json::value &jrequest)
{
    web::json::value jresponse;
    const web::json::value &japi = jrequest.at(JSON_API);
    const json::value &jdata = jrequest.at(JSON_DATA);
    std::string apiName = utility::conversions::to_utf8string(japi.as_string());

    Common::Serializeable *obj = Common::SObjectFactory::CreateObject(apiName);
    Api::BaseInput *input = dynamic_cast<Api::BaseInput*>( obj );

    Json::FromJson(input, jdata);

    Api::BaseOutput *output = input->Process();

    jresponse = Json::ToJson(output);

    return jresponse;
}
