/* 
 * File:   PassWordEncoder.h
 * 
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


#ifndef PASSWORD_ENCODER_H
#define PASSWORD_ENCODER_H

#include "WtHashGenerator.h"
#include "HashGenerator.h"
#include "RndGenerator.h"
#include "SingleTon.h"
#include "WtRndGenerator.h"
#include <string>

namespace Cipher {

class PasswordEncoder : public Common::Disposable {
private:
    MAKE_SINGLE_TON(PasswordEncoder)
    
public:
    std::string Encode(const std::string &passwd, const std::string &salt);
    bool Match(const std::string &passwd, const std::string &salt, const std::string &hash);
    
    std::string HashMethodName();
    
    std::string GenerateSalt();
    
    void Dispose() override;
    
protected:
    PasswordEncoder();
    virtual ~PasswordEncoder();

private:
    HashGenerator *m_hasGenerator;
    RndGenerator *m_randGenerator;
};

}

#endif /* PASSWORDENCODER_H */

