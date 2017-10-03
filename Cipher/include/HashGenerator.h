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


#ifndef BASE_HASH_FUNCTION_H
#define BASE_HASH_FUNCTION_H

#include <string>
#include <Disposable.h>
#include "AppCommonDef.h"

namespace Cipher {

class HashGenerator : public Common::Disposable {
private:
    NON_COPY_NON_MOVE_ABLE(HashGenerator);
    
public:
    enum HashMethod {
        SHA1,
        BCRYPT,
        MD5
    };
       
    virtual std::string Name(HashMethod method) = 0;

    virtual bool Match(HashMethod method, const std::string &msg, const std::string &salt, const std::string &hash) = 0;
    virtual std::string Generate(HashMethod method, const std::string &msg, const std::string &salt) = 0;
    
protected:
    HashGenerator() = default;
    virtual ~HashGenerator() = default;
};

}


#endif /* BASE_HASH_FUNCTION_H */

