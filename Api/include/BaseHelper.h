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


#ifndef BASE_HELPER_H
#define BASE_HELPER_H

#include <cpprest/json.h>

namespace Api {

class BaseHelper {
public:
    BaseHelper() = default;
    virtual ~BaseHelper() = default;

    virtual void InitAndValidate() = 0;

    virtual void CheckPermission() = 0;

    virtual web::json::value Execute() = 0;
};

}
#endif /* BASE_HELPER_H */

