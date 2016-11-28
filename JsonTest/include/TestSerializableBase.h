/*
 * Author: Rezaul Karm
 * Email: rkjohny@gmail.com
 *
 * Copyright (C) 2016 Rezaul Karim (rkjohny@gmail.com)
 *     The information contained here-in is the property of Rezaul Karim and
 *     is not to be disclosed or used without prior written permission of Rezaul Karim.
 *     This copyright extends to all media in which this information may be preserved
 *     including magnetic storage, computer print-out or visual display.
 *     Please refer to License.txt file for more details.
 */

#ifndef SERIALIZABLE_H
#define SERIALIZABLE_H

#include <string>
#include "Json.h"

namespace Json {

    class TestSerializableBase {
    public:
        TestSerializableBase() = default;
        virtual ~TestSerializableBase() = default;

        virtual const char* GetClassName() const = 0;

        REGISTER_GETTER_START
        REGISTER_GETTER_END

        REGISTER_SETTER_START
        REGISTER_SETTER_END
    };

} // namespace Json

#endif // SERIALIZABLE_H
