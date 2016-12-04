/**
 * Serializable.h
 *
 *      Author: rezaul
 *
 * Copyright (C) 2016 Rezaul Karim, rkjohny@gmail.com. All rights reserved.
 * Nobody should use this file without taking written permission from the author.
 */

#ifndef SERIALIZEABLE_H_
#define SERIALIZEABLE_H_

#include <cpprest/json.h>
#include "Json.h"

namespace Json {
    using namespace std;

    class Serializable {
    public:
        Serializable();
        virtual ~Serializable();

        virtual web::json::value Serialize() = 0;
        virtual void Deserialize(const web::json::value&) = 0;


        REGISTER_OWN_GETTER_START
        REGISTER_OWN_GETTER_END

        REGISTER_OWN_SETTER_START
        REGISTER_OWN_SETTER_END
    };

} /* namespace Api */

#endif /* SERIALIZEABLE_H_ */
