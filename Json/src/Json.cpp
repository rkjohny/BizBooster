/*
 * Author: Rezaul Karm
 * Email: rkjohny@gmail.com
 *
 * Copyright (C) 2016 Rezaul Karim (rkjohny@gmail.com)
 *     The information contained here-in is the property of Rezaul Karim and
 *     is not to be disclosed or used without prior written permission of Rezaul Karim.
 *     This copyright extends to all media in which this information may be preserved
 *     including magnetic storage, computer print-out or visual display.
 *     Please refer to License.txt file for more details.
 */

#include "Json.h"
#include "Common.h"

namespace Json
{

static bool loaded = false;
void LoadLibrary()
{
    if (!loaded) {
        Common::LoadLibrary();
        loaded = true;
    }
}

}
