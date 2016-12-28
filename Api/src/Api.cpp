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

#include "Api.h"
#include "Json.h"
#include "RegisterUserInput.h"
#include "RegisterUserOutput.h"
#include "Common.h"
#include "Dal.h"
#include "SOFactory.h"

namespace Api {

static bool g_loaded = false;

void LoadLibrary()
{
    if (!g_loaded) {
        Common::LoadLibrary();
        Json::LoadLibrary();

        Dal::LoadLibrary();

        REGISTER_CLASS(RegisterUserInput, "register_user");
        REGISTER_CLASS(RegisterUserInput, "RegisterUserInput");
        REGISTER_CLASS(RegisterUserOutput, "RegisterUserOutput");

        g_loaded = true;
    }
}

void ReleaseLibrary()
{
    if (g_loaded) {

        UNREGISTER_CLASS(RegisterUserInput, "register_user");
        UNREGISTER_CLASS(RegisterUserInput, "RegisterUserInput");
        UNREGISTER_CLASS(RegisterUserOutput, "RegisterUserOutput");
        
        Dal::ReleaseLibrary();
        
        g_loaded = false;
    }
}

} /* namespace  */
