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

#include "OpenSSLHWRNG.h"
#include "LogFactory.h"

#include <stdlib.h>
#include <assert.h>

#include <openssl/evp.h>
#include <openssl/err.h>
#include <openssl/engine.h>

// #include <openssl/fips.h>

//typedef unsigned char byte;
extern unsigned int OPENSSL_ia32cap_P[];
extern void OPENSSL_cpuid_setup(void);

#define UNUSED(x) ((void)(x))

namespace LCrypto {

bool OpenSSLHWRNG::m_isopened = false;
ENGINE* OpenSSLHWRNG::eng1 = nullptr;
ENGINE* OpenSSLHWRNG::eng2 = nullptr;

OpenSSLHWRNG::OpenSSLHWRNG()
{
}

OpenSSLHWRNG::~OpenSSLHWRNG()
{
    Close();
}

int OpenSSLHWRNG::Initialize()
{
    int ret = EXIT_FAILURE;
    unsigned long err = 0;
    int rc = 0;

    if (!m_isopened) {
        do {
            // This is called by OPENSSL_load_builtin_engines()
            OPENSSL_cpuid_setup();

            //rc = FIPS_mode_set(1);
            //err = ERR_get_error();
            //
            //assert(1 == rc);
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
            eng1 = ENGINE_by_id("rdrand");
            err = ERR_get_error();

            if (NULL == eng1) {
                FLOG_ERROR("ENGINE_load_rdrand failed, err = 0x%lx", err);
                break; /* failed */
            }

            // Make the assignment for proper cleanup (ENGINE_by_id needs one
            // cleanup, ENGINE_init needs a second distinct cleanup).
            rc = ENGINE_init((eng2 = eng1));
            err = ERR_get_error();

            if (0 == rc) {
                FLOG_ERROR("ENGINE_init failed, err = 0x%lx", err);
                break; /* failed */
            }

            /* Set the default RAND_method */
            rc = ENGINE_set_default(eng2, ENGINE_METHOD_RAND);
            err = ERR_get_error();

            if (1 != rc) {
                FLOG_ERROR("ENGINE_set_default failed, err = 0x%lx", err);
                break; /* failed */
            }

            /* Extra testing */
            ENGINE* t = ENGINE_get_default_RAND();
            err = ERR_get_error();
            if (t) ENGINE_free(t);

            assert(NULL != t);
            if (NULL == t) {
                FLOG_ERROR("ENGINE_get_default_RAND failed, err = 0x%lx", err);
                break; /* failed */
            }
            ret = EXIT_SUCCESS;

            m_isopened = true;

        } while (0);

        if (ret) {
            m_isopened = true;
            Close();
        }
    }

    return ret;
}

int OpenSSLHWRNG::GetRandomBytes(std::vector<uint8_t> &bytes, int length)
{
    uint8_t buffer[length] = {0};
    int rc;
    int err;

    rc = RAND_bytes(buffer, length);
    err = ERR_get_error();

    if (1 != rc) {
        FLOG_ERROR("RAND_bytes (1) failed, err = 0x%lx", err);
    } else {
        for (int i = 0; i < length; i++) {
            bytes.push_back(buffer[i]);
        }
    }
}

BaseRNG* OpenSSLHWRNG::GetInstance()
{
    if (!m_instance) {
        m_instance = new OpenSSLHWRNG();
    }
    return m_instance;
}

void OpenSSLHWRNG::Close()
{
    if (m_isopened) {

        if (eng2)
            ENGINE_finish(eng2);

        if (eng1)
            ENGINE_free(eng1);

        ENGINE_cleanup();

        m_isopened = false;
    }
}

}

