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

#ifndef BASE_RNG_H
#define BASE_RNG_H

#include <string>
#include <vector>

#include "AppCommonDef.h"
#include "SingleTon.h"

namespace Cipher {

class RndGenerator : public Common::Disposable {
private:
    NON_COPY_NON_MOVE_ABLE(RndGenerator);
    
public:
    virtual bool Initialize() = 0;
    virtual bool GetRandomBytes(std::vector<uint8_t> &bytes, int length) = 0;
    virtual bool GetRandomBytes(std::string &bytes, int length) = 0;
    virtual std::string GetRandomBytes(int length) = 0;
    
    bool IsInitialized() const {
        return m_isInitialized;
    }

protected:
    RndGenerator() : m_isInitialized(false) {}
    virtual ~RndGenerator() = default;
    bool m_isInitialized;
    
};

}

#endif /* BASE_RNG_H */

