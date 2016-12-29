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

#include <memory>

#include "InternalRootRequester.h"

namespace Dal {

const std::shared_ptr<User> InternalRootRequester::GetUser()
{
    return null_ptr;
}

bool InternalRootRequester::HasRole(const std::string &)
{
    return true;
}

bool InternalRootRequester::HasRole(const Role &)
{
    return true;
}

}

