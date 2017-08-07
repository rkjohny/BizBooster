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

#ifndef ENTITY_STATUS_H
#define ENTITY_STATUS_H

#include <string>
#include "AppCommonDef.h"


namespace Cruxdb {

enum Status
{
    V = 0, //valid
    D  //deleted
};

struct StatusStr
{
    static constexpr char *V = "V";
    static constexpr char *D = "D";
};

class StatusUtils {
private:
    MAKE_STATIC(StatusUtils);
    
public:
    static std::string ToStr(const Status &status) noexcept(false);
    
    static Status ToStatus(const std::string &status) noexcept(false);
    
};

}
#endif //ENTITY_STATUS_H
