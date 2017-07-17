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

#ifndef CONVERTER_H
#define CONVERTER_H

#include <memory>
#include <string>
#include <stdexcept>
#include <vector>

#include "AppCommonDef.h"

namespace Common {

    class Converter {
    private:
        MAKE_STATIC(Converter);

    public:

        template<typename Derived, typename Base>
        std::unique_ptr<Derived> static DynamicDownCast(std::unique_ptr<Base> &&p)
        {
            static_assert(std::is_base_of< Base, Derived >::value, "Incompatible types");
            if(Derived *result = dynamic_cast<Derived *>(p.get())) {
                p.release();
                return std::unique_ptr<Derived>(result);
            }
            return std::unique_ptr<Derived>(nullptr);
        }

        template<typename Derived, typename Base>
        std::unique_ptr<Base> static DynamicUpCast(std::unique_ptr<Derived> &&p)
        {
            static_assert(std::is_base_of< Base, Derived >::value, "Incompatible types");

            if(Base *result = dynamic_cast<Base *>(p.get())) {
                p.release();
                return std::unique_ptr<Base>(result);
            }
            return std::unique_ptr<Base>(nullptr);
        }


        static int64_t ToInt32(const std::string &num, int8_t base = 10) noexcept(false);

        static std::string ToStr(int32_t n, int8_t base = 10);
        
        static std::string ToHexStr(const std::vector<uint8_t> &vec);
        static std::string ToHexStr(const uint8_t *arr, int length);

    };
}

#endif //CONVERTER_H
