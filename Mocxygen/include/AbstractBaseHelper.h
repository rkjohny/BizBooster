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


#ifndef BASE_HELPER_H
#define BASE_HELPER_H

#include "AppCommonDef.h"
#include "AbstractBaseOutput.h"
#include <cpprest/json.h>

namespace Mocxygen {

class AbstractBaseHelper {
private:
    NON_COPY_NON_MOVE_ABLE(AbstractBaseHelper);
    
public:    
    AbstractBaseHelper() = default;
    virtual ~AbstractBaseHelper() = default;


    virtual std::shared_ptr<AbstractBaseOutput> Execute() = 0;
};

}
#endif /* BASE_HELPER_H */

