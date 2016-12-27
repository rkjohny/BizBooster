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


enum Status
{
    V = 0, //valid
    D  //deleted
};


class StatusUtils {
private:
    MAKE_STATIC(StatusUtils);
    
public:
    
    static std::string ToStr(const Status &status)
    {
        switch (status) {
            case Status::V:
                return STATUS_V_STR;
            
            case Status::D:
                return STATUS_D_STR;
            
            default:
                throw std::runtime_error("Invalid status");
        }
    }
    
    static Status ToStatus(const std::string &&status)
    {
        if (status.compare(STATUS_V_STR) == 0) {
            return Status::V;
        }
        if (status.compare(STATUS_D_STR) == 0) {
            return Status::D;
        }
        
        throw std::runtime_error("invalid status found");
    }
    
    static Status ToStatus(const std::string &status)
    {
        return ToStatus(std::move(status));
    }
};

#endif //ENTITY_STATUS_H
