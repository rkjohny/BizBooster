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

#include "OsslHwRandGenerator.h"
#include "LoggerFactory.h"
#include "Converter.h"

//#include <openssl/evp.h>
#include <openssl/err.h>
#include <openssl/engine.h>
// #include <openssl/fips.h>


#ifdef __cplusplus
extern "C" {
#endif

    extern unsigned int OPENSSL_ia32cap_P[];
    extern void OPENSSL_cpuid_setup(void);

#ifdef __cplusplus
}
#endif


namespace Cipher {

    ENGINE* OsslHwRandGenerator::cm_engFoundById = nullptr;
    ENGINE* OsslHwRandGenerator::cm_engInitialized = nullptr;
    boost::mutex OsslHwRandGenerator::cm_mutex;

    OsslHwRandGenerator::OsslHwRandGenerator() {
        if (!m_isInitialized) {
            m_isInitialized = OsslHwRandGenerator::Initialize();
            if (m_isInitialized) {
                m_isDisposed = false;
            }
        }
    }

    OsslHwRandGenerator::~OsslHwRandGenerator() {
        if (!m_isDisposed) {
            Dispose();
        }
    }

    bool OsslHwRandGenerator::Initialize() {
        int ret = EXIT_FAILURE;
        unsigned long err = 0;
        int rc = 0;

        do {
            // This is called by OPENSSL_load_builtin_engines()
            OPENSSL_cpuid_setup();

            //rc = FIPS_mode_set(1);
            //err = ERR_get_error();
            //
            //if(1 != rc) {
            //    fprintf(stderr, "FIPS_mode_set failed, err = 0x%lx\n", err);
            //    break; /* failed */
            //}

            int rdrand = OPENSSL_ia32cap_P[1] & (1 << (62 - 32));
            if (rdrand) {
                FLOG_INFO("rdrand is available");
            } else {
                FLOG_INFO("rdrand is not available");
            }

            /* Load the engine of interest */
            ENGINE_load_rdrand();
            cm_engFoundById = ENGINE_by_id("rdrand");
            err = ERR_get_error();

            if (NULL == cm_engFoundById) {
                FLOG_ERROR("ENGINE_load_rdrand failed, err = 0x%lx", err);
                break; /* failed */
            }

            // Make the assignment for proper cleanup (ENGINE_by_id needs one
            // cleanup, ENGINE_init needs a second distinct cleanup).
            rc = ENGINE_init((cm_engInitialized = cm_engFoundById));
            err = ERR_get_error();

            if (0 == rc) {
                FLOG_ERROR("ENGINE_init failed, err = 0x%lx", err);
                break; /* failed */
            }

            /* Set the default RAND_method */
            rc = ENGINE_set_default(cm_engInitialized, ENGINE_METHOD_RAND);
            err = ERR_get_error();

            if (1 != rc) {
                FLOG_ERROR("ENGINE_set_default failed, err = 0x%lx", err);
                break; /* failed */
            }

            /* Extra testing */
            ENGINE* t = ENGINE_get_default_RAND();
            err = ERR_get_error();
            if (t) ENGINE_free(t);

            if (NULL == t) {
                FLOG_ERROR("ENGINE_get_default_RAND failed, err = 0x%lx", err);
                break; /* failed */
            }

            ret = EXIT_SUCCESS;

        } while (0);

        return (ret == EXIT_SUCCESS);
    }

    bool OsslHwRandGenerator::DoGetRandomBytes(uint8_t *buffer, int length) {
        int rc;
        int err;

        rc = RAND_bytes(buffer, length);
        err = ERR_get_error();

        if (rc != 1) {
            FLOG_ERROR("RAND_bytes (1) failed, err = 0x%lx", err);
            return false;
        }
        return true;
    }

    bool OsslHwRandGenerator::GetRandomBytes(std::vector<uint8_t> &bytes, int length) {
        uint8_t *buffer = new uint8_t[length / 2];

        boost::lock_guard<boost::mutex> guard(cm_mutex);
        bool ret = DoGetRandomBytes(buffer, length / 2);
        
        if (ret) {
            for (int i = 0; i < length / 2; i++) {
                bytes.push_back(buffer[i]);
            }
        }

        delete buffer;
        return ret;
    }

    bool OsslHwRandGenerator::GetRandomBytes(std::string &bytes, int length) {
        uint8_t *buffer = new uint8_t[length / 2];

        boost::lock_guard<boost::mutex> guard(cm_mutex);
        bool ret = DoGetRandomBytes(buffer, length / 2);

        if (ret) {
            for (int i = 0; i < length / 2; i++) {
                bytes = Common::Converter::ToHexStr(buffer, length / 2);
            }
        }
        
        delete buffer;
        return ret;
    }

    std::string OsslHwRandGenerator::GetRandomBytes(int length) {
        std::string randomBytes;
        GetRandomBytes(randomBytes, length);
        return randomBytes;
    }

    void OsslHwRandGenerator::Dispose() {
        if (cm_engInitialized)
            ENGINE_finish(cm_engInitialized);

        cm_engInitialized = nullptr;

        if (cm_engFoundById)
            ENGINE_free(cm_engFoundById);

        cm_engFoundById = nullptr;

        ENGINE_cleanup();

        m_isInitialized = false;
        m_isDisposed = true;
    }

}

