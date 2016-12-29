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


#ifndef SINGLE_TON_H
#define SINGLE_TON_H

#include <mutex>
#include "Disposable.h"

namespace Common {


class SingleTon : public Common::Disposable {
protected:
    SingleTon() = default;
    virtual ~SingleTon() = default;
    
    std::mutex m_mutex;
    
};

}
#endif /* SINGLE_TON_H */

