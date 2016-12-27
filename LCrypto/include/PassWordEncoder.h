/* 
 * File:   PassWordEncoder.h
 * 
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


#ifndef PASSWORD_ENCODER_H
#define PASSWORD_ENCODER_H

#include "WtHashGenerator.h"
#include "HashGenerator.h"
#include <string>

namespace LCrypto {

class PassWordEncoder {
public:
    static PassWordEncoder* GetInstance();
    std::string Encode(std::string passwd, std::string salt);
    bool Match(std::string passwd, std::string hash, std::string salt);
    
    std::string HasHMethod();
    
private:
    HashGenerator *m_hasGenerator;
    static PassWordEncoder *m_instance;
    
    PassWordEncoder();
    virtual ~PassWordEncoder();
    NON_COPY_NON_MOVE_ABLE(PassWordEncoder);
};

}

#endif /* PASSWORDENCODER_H */

