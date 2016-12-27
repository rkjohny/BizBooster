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


#ifndef LCRYPTO_H
#define LCRYPTO_H

#include "HashGenerator.h"


namespace LCrypto {

void LoadLibrary();
void ReleaseLibrary();

HashGenerator *GetHashGenerator();

}

#endif /* LCRYPTO_H */

