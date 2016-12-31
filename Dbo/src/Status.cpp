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

#include "Status.h"
#include <stdexcept>

namespace Dal {

std::string StatusUtils::ToStr(const Status &status)
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

Status StatusUtils::ToStatus(const std::string &status)
{
    if (status.compare(STATUS_V_STR) == 0) {
        return Status::V;
    }
    if (status.compare(STATUS_D_STR) == 0) {
        return Status::D;
    }

    throw std::runtime_error("invalid status found");
}

}