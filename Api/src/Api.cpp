

#include "Api.h"
#include "Json.h"
#include "RegisterUserInput.h"
#include "RegisterUserOutput.h"
#include "Common.h"

namespace Api
{

static bool loaded = false;
void LoadLibrary()
{
    if (!loaded) {
        Common::LoadLibrary();
        Json::LoadLibrary();

        SOFactory::Load();    
        REGISTER_CLASS(RegisterUserInput, "register_user");
        REGISTER_CLASS(RegisterUserInput, "RegisterUserInput");
        REGISTER_CLASS(RegisterUserOutput, "RegisterUserOutput");
        REGISTER_CLASS(User, "User");

        loaded = true;
    }
}


} /* namespace  */
