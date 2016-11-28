

#include "Api.h"
#include "Json.h"
#include "RegisterUserInput.h"
#include "RegisterUserOutput.h"
#include "Common.h"

namespace Api
{

void LoadLibrary()
{
    Common::LoadLibrary();
    Json::LoadLibrary();
    
    SOFactory::Load();    
    REGISTER_CLASS(RegisterUserInput, "register_user");
    REGISTER_CLASS(RegisterUserInput, "RegisterUserInput");
    REGISTER_CLASS(RegisterUserOutput, "RegisterUserOutput");
    REGISTER_CLASS(User, "User");
}


} /* namespace  */
