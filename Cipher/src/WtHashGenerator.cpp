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

#include "WtHashGenerator.h"
#include "CipherDef.h"

namespace Cipher {

    WtHashGenerator::WtHashGenerator() : m_bcryptHash(BCRYPT_HASH_NUMBER_OF_ITERATION) {

    }

    WtHashGenerator::~WtHashGenerator() {
        Dispose();
    }

    std::string WtHashGenerator::Name(HashMethod method) {
        std::string name = "";

        switch (method) {
            case SHA1:
                name = m_sha1Hash.name();
                break;
            case BCRYPT:
                name = m_bcryptHash.name();
                break;
            case MD5:
                name = m_md5Hash.name();
                break;
        }
        return name;
    }

    bool WtHashGenerator::Match(HashMethod method, const std::string &msg, const std::string &salt,
                                const std::string &hash) {
        bool ret = false;

        switch (method) {
            case SHA1:
                ret = m_sha1Hash.verify(msg, salt, hash);
                break;

            case BCRYPT:
                ret = m_bcryptHash.verify(msg, salt, hash);
                break;
            case MD5:
                ret = m_md5Hash.verify(msg, salt, hash);
                break;
        }
        return ret;
    }

    std::string WtHashGenerator::Generate(HashMethod method, const std::string &msg, const std::string &salt) {
        std::string hash = "";

        switch (method) {
            case SHA1:
                hash = m_sha1Hash.compute(msg, salt);
                break;

            case BCRYPT:
                hash = m_bcryptHash.compute(msg, salt);
                break;
            case MD5:
                hash = m_md5Hash.compute(msg, salt);
        }
        return hash;
    }

    void WtHashGenerator::Dispose() {
        if (!m_isDisposed) {
            //do stuff
            m_isDisposed = true;
        }
    }

}