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

#ifndef DISPOSABLE_H
#define DISPOSABLE_H

namespace Common {
    class Disposable {
    protected:
        bool m_isDisposed;
        
    public:
        Disposable();
        virtual ~Disposable();
        virtual void Dispose() = 0;
        
        bool IsDisposed() const {
            return m_isDisposed;
        }
    };

} /* namespace Common */

#endif /* DISPOSABLE_H */
