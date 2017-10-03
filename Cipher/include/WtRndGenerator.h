
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

#ifndef WT_RND_GENERATOR_H
#define WT_RND_GENERATOR_H

#include "RndGenerator.h"
#include "Disposable.h"
#include "Wt/WRandom.h"


namespace Cipher {

    class WtRndGenerator : public RndGenerator {
        MAKE_SINGLE_TON(WtRndGenerator)

    protected:
        WtRndGenerator();
        virtual ~WtRndGenerator();

    public:
        void Dispose() override;
        bool Initialize() override;
        bool GetRandomBytes(std::vector<uint8_t> &bytes, int length) override;
        bool GetRandomBytes(std::string &bytes, int length) override;
        std::string GetRandomBytes(int length) override;;

    private:
        Wt::WRandom m_wtRanGenerator;
    };
}


#endif //WT_RND_GENERATOR_H
