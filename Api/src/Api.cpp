

#include "Api.h"
#include "Json.h"
#include "RegisterUserInput.h"

namespace Api
{

void LoadLibrary()
{
    Json::LoadLibrary();
    
    REGISTER_CLASS(RegisterUserInput, "register_user")
}


} /* namespace  */
