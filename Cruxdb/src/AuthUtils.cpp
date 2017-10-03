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

#include "AuthUtils.h"
#include "LibCipher.h"
#include "CipherDef.h"

namespace Cruxdb {

    std::string AuthUtils::GenerateEmailToken(Cipher::HashGenerator::HashMethod hashMethod, std::string &salt) {
        auto randGenerator = Cipher::GetRndGenerator();
        auto hashGenerator = Cipher::GetHashGenerator();

        std::string randomBytes = randGenerator->GetRandomBytes(RANDOM_TOKEN_LENGTH);
        return hashGenerator->Generate(hashMethod, randomBytes, salt);
    }

    std::string AuthUtils::GenerateSalt() {
        auto randGenerator = Cipher::GetRndGenerator();
        return randGenerator->GetRandomBytes(PASSWORD_SALT_LENGTH);
    }

    std::string AuthUtils::Encode(Cipher::HashGenerator::HashMethod hashMethod, std::string &msg, std::string &salt) {
        auto hashGenerator = Cipher::GetHashGenerator();
        return hashGenerator->Generate(hashMethod, msg, salt);
    }

    std::string AuthUtils::HashMethodName(Cipher::HashGenerator::HashMethod hashMethod) {
        auto hashGenerator = Cipher::GetHashGenerator();
        return hashGenerator->Name(hashMethod);
    }

    bool AuthUtils::Match(Cipher::HashGenerator::HashMethod hashMethod, const std::string &msg, const std::string &salt,
                             const std::string &hash) {
        auto hashGenerator = Cipher::GetHashGenerator();
        return hashGenerator->Match(hashMethod, msg, salt, hash);
    }

}