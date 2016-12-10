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

#ifndef TINY_JSON_SETTER_H
#define TINY_JSON_SETTER_H

namespace Json {

    template<class ClassT, class ArgT >
    class Setter {
    public:
        using Class = ClassT;
        using Type = ArgT;

        typedef void ( Class::*SetterPtr)(ArgT);
        SetterPtr fp;
        const char *name;

        constexpr Setter(SetterPtr fp, const char* name) :
        fp{fp}, name{ name}
        {
        }

    }; //Class Setter

} // namespace Json

#endif //TINY_JSON_SETTER_H
