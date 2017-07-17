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


#ifndef LIB_CIPHER_DEF_H
#define LIB_CIPHER_DEF_H


#define OPENSSL_USE_DEPRECATED

#define WT_HASH_FUNCTION

#define OPEN_SSL_CRYPTO_ENGINE

//column size == 100
#define PASSWORD_HASH_LENGTH 100  

//column size == 20
#define PASSWORD_SALT_LENGTH 20

//column size = 64
#define EMAIL_TOKEN_LENGTH 64

//column size = 64
#define AUTH_TOKEN_LENGTH 64

#define HASH_METHOD_SHA1 "sha1"
#define HASH_METHOD_BCRYPT "bcrypt"

#endif /* LIB_CIPHER_DEF_H */

