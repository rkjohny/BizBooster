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

#ifndef WT_HASH_FUNCTION_H
#define WT_HASH_FUNCTION_H

#include "AppDef.h"
#include "BaseHashFunction.h"
#include <Wt/Auth/HashFunction>
#include <string>

#define BCRYPT_ITERATION 10

namespace Common {

class WtHashFunction : public BaseHashFunction {
public:
    WtHashFunction();
    virtual ~WtHashFunction() = default;
    
    std::string Name(HasMethod method) override;
    
    bool Verify(HasMethod method, const std::string &msg, const std::string &hash, const std::string &salt) override;
    std::string Generate(HasMethod method, const std::string &msg, const std::string &salt) override;

private:
    Wt::Auth::BCryptHashFunction m_bcryptHash;
    Wt::Auth::SHA1HashFunction m_sha1Hash;
};

}
#endif /* WT_HASH_FUNCTION_H */

