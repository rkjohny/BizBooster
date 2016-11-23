#include "RequestHandler.h"
#include "BaseInput.h"
#include "Deserializer.h"
#include "AppFactory.h"
#include "BaseOutput.h"

#include <string>
#include <cpprest/asyncrt_utils.h>
#include <cpprest/json.h>


using namespace Server;
using namespace Api;
using namespace Common;



void RequestHandler:: HandleGetRequest( web::http::http_request& request )
{

}

void RequestHandler::HandlePutRequest( web::http::http_request& request )
{

}

void RequestHandler::HandlePostRequest( web::http::http_request& request )
{

    request
    .extract_json()
    .then( [&]( pplx::task<web::json::value> task )
    {
        try
        {
            web::json::value&& jvalue = task.get();

// 			Serializeable* sObject = Deserializer::Deserialize ( jvalue );
// 			BaseInput* input = dynamic_cast<BaseInput*> (sObject);
// 			BaseOutput *outPut = NULL;
//
// 			if (input != NULL) {
// 				std::shared_ptr<BaseInput> entityObj ( input );
// 				outPut = input->Process();
// 			}
//
// 			if (outPut != NULL) {
//
// 			}

            //std::shared_ptr<BaseOutput> output ( input->Process() );
            //std::shared_ptr<BaseOutput> output2 ( ServiceFacade::RegisterUser ( dynamic_cast<RegisterUserInput*>( input.get() ) ) );
            //RegisterUserInput* in = new RegisterUserInput();
            //RegisterUserOutput* out = new RegisterUserOutput();
            //delete in;
            //delete out;

        }
        catch ( exception e )
        {
            LOG_ERROR( e.what() );
        }

        //input.as_array();
    } ).wait();
}

void RequestHandler::HandleDeleteRequest( web::http::http_request& request )
{

}
