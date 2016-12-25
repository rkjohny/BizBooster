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

#ifndef BASE_RNG_H
#define BASE_RNG_H

#include <string>
#include <vector>

#include "AppDef.h"

namespace LCrypto {

class BaseRNG {
public:
    virtual int Initialize() = 0;
    virtual int GetRandomBytes(std::vector<uint8_t> &bytes, int length) = 0;
    virtual BaseRNG* GetInstance() = 0;
    virtual void Close() = 0;
    
protected:
    BaseRNG(); 
    virtual ~BaseRNG();
    NON_COPY_NON_MOVE_ABLE(BaseRNG);   
};

}

#endif /* BASE_RNG_H */

