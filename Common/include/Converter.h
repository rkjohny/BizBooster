//
// Created by rezaul on 11/29/16.
//

#ifndef BIZBOOSTER_UTILS_H
#define BIZBOOSTER_UTILS_H

#include <memory>


namespace Common {

    class Converter {
    private:
        Converter() = delete;

    public:

        template<typename Derived, typename Base>
        std::unique_ptr<Derived> static StaticDownCast(std::unique_ptr<Base> &&p)
        {
            static_assert(std::is_base_of< Base, Derived >::value, "Derived must be derived from Base");
            auto d = static_cast<Derived *>(p.release());
            return std::unique_ptr<Derived>(d);
        }

        template<typename Derived, typename Base>
        std::unique_ptr<Derived> static DynamicDownCast(std::unique_ptr<Base> &&p)
        {
            static_assert(std::is_base_of< Base, Derived >::value, "Derived must be derived from Base");
            if(Derived *result = dynamic_cast<Derived *>(p.get())) {
                p.release();
                return std::unique_ptr<Derived>(result);
            }
            return std::unique_ptr<Derived>(nullptr);
        }
    };
}

#endif //BIZBOOSTER_UTILS_H
