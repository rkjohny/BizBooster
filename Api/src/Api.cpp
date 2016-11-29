

#include "Api.h"
#include "Json.h"
#include "RegisterUserInput.h"
#include "RegisterUserOutput.h"
#include "Common.h"

namespace Api {

static bool loaded = false;

void LoadLibrary()
{
    if (!loaded) {
        Common::LoadLibrary();
        Json::LoadLibrary();

        Api::ClassRegistrar<RegisterUserInput> r( "key" );
        std::string s ="key2";
        std::string s3 ="key3";
        Api::ClassRegistrar<RegisterUserInput> r2( std::move(s) );
        Api::ClassRegistrar<RegisterUserInput> r3( s3 );

        SOFactory::Load();
        REGISTER_CLASS(RegisterUserInput, "register_user");
        REGISTER_CLASS(RegisterUserInput, "RegisterUserInput");
        REGISTER_CLASS(RegisterUserOutput, "RegisterUserOutput");
        REGISTER_CLASS(User, "User");

        loaded = true;
    }
}


} /* namespace  */
