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

#ifndef BOOST_RAND_GENERATOR_H
#define BOOST_RAND_GENERATOR_H

#include "RndGenerator.h"
#include "CipherDef.h"
#include "boost/random/random_device.hpp"

namespace Cipher {

    class BoostRandGenerator : public RndGenerator {
        MAKE_SINGLE_TON(BoostRandGenerator);

    protected:
        BoostRandGenerator();
        virtual ~BoostRandGenerator();

    public:
        void Dispose() override;
        bool Initialize() override;
        bool GetRandomBytes(std::vector<uint8_t> &bytes, int length) override;
        bool GetRandomBytes(std::string &bytes, int length) override;

    private:
        boost::random_device m_boostRandDevice;       
    };

}

#endif /* BOOST_RAND_GENERATOR_H */

