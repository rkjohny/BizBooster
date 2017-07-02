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

#include "Status.h"
#include <stdexcept>

namespace Cruxdb {

std::string StatusUtils::ToStr(const Status &status)
{
    switch (status) {
    case Status::V:
        return StatusStr::V;

    case Status::D:
        return StatusStr::D;

    default:
        throw std::runtime_error("Invalid status");
    }
}

Status StatusUtils::ToStatus(const std::string &status)
{
    if (status.compare(StatusStr::V) == 0) {
        return Status::V;
    }
    if (status.compare(StatusStr::D) == 0) {
        return Status::D;
    }

    throw std::runtime_error("invalid status found");
}

}