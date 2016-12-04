//
// Created by rezaul on 12/4/16.
//

#include "Dal.h"
#include "SOFactory.h"
#include "Json.h"
#include "User.h"

namespace Dal {

    static bool loaded = false;

    void LoadLibrary()
    {
        if (!loaded) {
            Json::LoadLibrary();

            REGISTER_CLASS(User, "user");

            loaded = true;
        }
    }
}