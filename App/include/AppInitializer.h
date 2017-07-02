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

#ifndef APP_INITIALIZER_H
#define APP_INITIALIZER_H

#include "AppCommonDef.h"

namespace BizBooster {

class AppInitializer {
public:
    static void Initialize();
    
private:
    MAKE_STATIC(AppInitializer);
};

}
#endif /* APP_INITIALIZER_H */

