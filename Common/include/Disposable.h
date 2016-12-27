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

#ifndef DISPOSABLE_H
#define DISPOSABLE_H

namespace Common {

    class Disposable {
    protected:
        bool m_isDosposed;
        bool m_isInitialized;

    public:
        Disposable();
        virtual ~Disposable();
        virtual void Dispose() = 0;
    };

} /* namespace Common */

#endif /* DISPOSABLE_H */
