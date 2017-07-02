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

#ifndef CMARSHAL_JSON_SETTER_H
#define CMARSHAL_JSON_SETTER_H

namespace Cmarshal {
    namespace Json {

        template<class ClassT, class ArgT>
        class Setter {
        public:
            using Class = ClassT;
            using Type = ArgT;

            typedef void ( Class::*SetterPtr)(ArgT);

            SetterPtr fp;
            const char *name;

            constexpr Setter(SetterPtr fp, const char *name) :
                    fp{fp}, name{name} {
            }

        }; //Class Setter

    } // namespace Json
} // namespace Cmarshal

#endif //CMARSHAL_JSON_SETTER_H
