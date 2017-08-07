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

#ifndef AUTH_UTILS_H
#define AUTH_UTILS_H

#include "AppCommonDef.h"
#include <string>

namespace Cruxdb {

class AuthUtils {
private:
    MAKE_STATIC(AuthUtils);
    
public:
    static std::string GenerateEmailToken();

};

}
#endif /* AUTH_UTILS_H */

