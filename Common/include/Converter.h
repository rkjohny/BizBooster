//
// Created by rezaul on 11/29/16.
//

#ifndef BIZBOOSTER_UTILS_H
#define BIZBOOSTER_UTILS_H

#include <memory>
#include <string>
#include <stdexcept>

namespace Common {

    class Converter {
    private:
        Converter() = delete;

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


        static int64_t ToInt32(std::string&& num, int8_t base = 10) throw (std::invalid_argument, std::out_of_range);

        static std::string ToStr(int32_t n, int8_t base = 10);

    };
}

#endif //BIZBOOSTER_UTILS_H
