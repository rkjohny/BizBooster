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

#include "RndGenerator.h"
#include "AppCommonDef.h"
#include <HashGenerator.h>
#include <string>

namespace Cruxdb {


class AuthUtils {
private:
    MAKE_STATIC(AuthUtils);
    
public:
    static std::string GenerateEmailToken(Cipher::HashGenerator::HashMethod hashMethod, std::string &salt);
    static std::string GenerateSalt();
    static std::string Encode(Cipher::HashGenerator::HashMethod hashMethod, std::string &msg, std::string &salt);
    static std::string HashMethodName(Cipher::HashGenerator::HashMethod hashMethod);
    static bool Match(Cipher::HashGenerator::HashMethod hashMethod, const std::string &msg, const std::string &salt,
                         const std::string &hash);
};

}
#endif /* AUTH_UTILS_H */

