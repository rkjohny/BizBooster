/*
 * Author: Rezaul Karm
 * Email: rkjohny@gmail.com
 *
 * Copyright (C) 2017 Rezaul Karim (rkjohny@gmail.com)
 *     The information contained here-in is the property of Rezaul Karim and
 *     is not to be disclosed or used without prior written permission of Rezaul Karim.
 *     This copyright extends to all media in which this information may be preserved
 *     including magnetic storage, computer print-out or visual display.
 *     Please refer to License.txt file for more details.
 */

#include "Json.h"
#include "LibCommon.h"

namespace Cmarshal {
    namespace Json {

        static bool g_loaded = false;

        void LoadLibrary() {
            if (!g_loaded) {
                Common::LoadLibrary();
                g_loaded = true;
            }
        }

        void ReleaseLibrary() {
            if (g_loaded) {

                Common::ReleaseLibrary();

                g_loaded = false;
            }

        }

    }
}
