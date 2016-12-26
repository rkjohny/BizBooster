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

#ifndef OPENSSLIMPORT_H
#define OPENSSLIMPORT_H

#ifdef __cplusplus
extern "C" {
#endif

#include <openssl/ossl_typ.h>
#include <openssl/evp.h>
#include <openssl/err.h>
#include <openssl/engine.h>


extern unsigned int OPENSSL_ia32cap_P[];
extern void OPENSSL_cpuid_setup(void);


#ifdef __cplusplus
}
#endif

#endif /* OPENSSLIMPORT_H */

