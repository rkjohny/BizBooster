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

#ifndef ENTITY_STATUS_H
#define ENTITY_STATUS_H

#include <string>
#include "AppDef.h"


#define STATUS_V_STR  "V"
#define STATUS_D_STR  "D"


namespace Dal {

enum Status
{
    V = 0, //valid
    D  //deleted
};

    
class StatusUtils {
private:
    MAKE_STATIC(StatusUtils);
    
public:
    
    static std::string ToStr(const Status &status);
    
    static Status ToStatus(const std::string &&status);
    
    static Status ToStatus(const std::string &status);
};

}
#endif //ENTITY_STATUS_H
