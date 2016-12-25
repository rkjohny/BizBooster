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


#ifndef BASE_HASH_FUNCTION_H
#define BASE_HASH_FUNCTION_H

#include <string>

namespace LCrypto {

class BaseHashFunction {
public:
    enum HasMethod {
        SHA1,
        BCRYPT
    };
    
    BaseHashFunction() = default;
    virtual ~BaseHashFunction() = default;
    
    virtual std::string Name(HasMethod method) = 0;
       
    virtual bool Verify(HasMethod method, const std::string &msg, const std::string &hash, const std::string &salt) = 0;
    virtual std::string Generate(HasMethod method, const std::string &msg, const std::string &salt) = 0;
};

}


#endif /* BASE_HASH_FUNCTION_H */

