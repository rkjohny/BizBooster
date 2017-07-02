/**
 * Author: Rezaul Karim
 * Email: rkjohny@gmail.com
 *
 * Copyright (C) 2017 Rezaul Karim (rkjohny@gmail.com) all rights reserved.
 *
 * The information contained here-in is the property of Rezaul Karim and is not to be
 * disclosed or used without prior written permission of Rezaul Karim. This copyright
 * extends to all media in which this information may be preserved including
 * magnetic storage, computer print-out or visual display.
 */

#include "LibMocxygen.h"
#include "Json.h"
#include "RegisterUserInput.h"
#include "RegisterUserOutput.h"
#include "LibCommon.h"
#include "LibCruxdb.h"
#include "SOFactory.h"
#include "LogInInput.h"
#include "LoggedInInput.h"

namespace Mocxygen {

static bool g_loaded = false;

void LoadLibrary()
{
    if (!g_loaded) {
        Common::LoadLibrary();
        Cmarshal::Json::LoadLibrary();

        Cruxdb::LoadLibrary();

        REGISTER_CLASS(RegisterUserInput, "register_user");
        REGISTER_CLASS(RegisterUserInput, "RegisterUserInput");
        REGISTER_CLASS(RegisterUserOutput, "RegisterUserOutput");
        
        REGISTER_CLASS(LogInInput, "login");
        REGISTER_CLASS(LoggedInInput, "loggedin" );

        g_loaded = true;
    }
}

void ReleaseLibrary()
{
    if (g_loaded) {

        UNREGISTER_CLASS(RegisterUserInput, "register_user");
        UNREGISTER_CLASS(RegisterUserInput, "RegisterUserInput");
        UNREGISTER_CLASS(RegisterUserOutput, "RegisterUserOutput");
        
        Cruxdb::ReleaseLibrary();
        
        g_loaded = false;
    }
}

} /* namespace  */
