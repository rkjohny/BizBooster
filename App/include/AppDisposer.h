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

#ifndef CLIENT_DISPOSER_H
#define CLIENT_DISPOSER_H

#include "AppCommonDef.h"

namespace BizBooster {

class AppDisposer {
private:
    MAKE_STATIC(AppDisposer);

public:
    static void Dispose();
};


}


#endif //CLIENT_DISPOSER_H
