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

#ifndef PANTOON_SERVICE_DISPOSER_H
#define PANTOON_SERVICE_DISPOSER_H

#include "AppCommonDef.h"

namespace Pantoon {

    class ServiceDisposer {
    private:
        MAKE_STATIC(ServiceDisposer);

    public:
        static void Dispose();
    };


} //namespace Pantoon

#endif /* PANTOON_SERVICE_DISPOSER_H */
