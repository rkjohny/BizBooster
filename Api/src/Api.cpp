

#include "Api.h"
#include "Json.h"
#include "RegisterUserInput.h"
#include "RegisterUserOutput.h"
#include "Common.h"
#include "Dal.h"

namespace Api {

static bool loaded = false;

void LoadLibrary()
{
    if (!loaded) {
        Common::LoadLibrary();
        Json::LoadLibrary();

        Dal::LoadLibrary();

        REGISTER_CLASS(RegisterUserInput, "register_user");
        REGISTER_CLASS(RegisterUserInput, "RegisterUserInput");
        REGISTER_CLASS(RegisterUserOutput, "RegisterUserOutput");

        loaded = true;
    }
}


} /* namespace  */
