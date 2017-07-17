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

#ifndef BLOCKEXECUTOR_H
#define BLOCKEXECUTOR_H


#include <functional>

namespace Mocxygen {

    class BlockExecutor {
    private:
        bool invoked;

    public:
        bool IsInvoked() const;

        void SetInvoked(bool invoked);

        void Execute(bool execute, std::function<void(void)> f) {
            if (f) {
                f();
                invoked = true;
            }
        }
    };

}


#endif //BLOCKEXECUTOR_H
