/**
 * Author: Rezaul Karim
 * Email: rkjohny@gmail.com
 *
 * Copyright (C) 20016 Rezaul Karim (rkjohny@gmail.com) all rights reserved.
 *
 * The information contained here-in is the property of Rezaul Karim and is not to be
 * disclosed or used without prior written permission of Rezaul Karim. This copyright
 * extends to all media in which this information may be preserved including
 * magnetic storage, computer print-out or visual display.
 */

#include "AuthUtils.h"
#include "RndGenerator.h"
#include "LCrypto.h"
#include "CryptoDef.h"

namespace  Dal {

std::string AuthUtils::GenerateEmailToken()
{
    std::string emailToken;

    LCrypto::RndGenerator *randGenerator = LCrypto::GetRndGenerator();
    randGenerator->GetRandomBytes(emailToken, EMAIL_TOKEN_LENGTH);

    return emailToken;
}

}