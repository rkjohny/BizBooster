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

#ifndef SHARED_OBJECT_H
#define SHARED_OBJECT_H

#include <mutex>

namespace Common {
    using namespace std;

    class SharedObject {
    protected:
        SharedObject() = default;
        virtual ~SharedObject() = default;

        mutex m_mutex;
    };

} /* namespace Common */

#endif /* SHARED_OBJECT_H */
