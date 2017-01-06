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

#ifndef TINY_JSON_SERIALIZEABLE_H
#define TINY_JSON_SERIALIZEABLE_H

#include <cpprest/json.h>
#include "Json.h"

namespace Json {
    using namespace std;

    class Serializable {
    public:
        Serializable() = default;
        virtual ~Serializable() = default;

        virtual const web::json::value& Serialize() = 0;
        virtual void Deserialize(const web::json::value&) = 0;


        REGISTER_GETTER_START
        REGISTER_GETTER_END

        REGISTER_SETTER_START
        REGISTER_SETTER_END
                
    protected:
        web::json::value m_serializedValue;
    };

} /* namespace Api */

#endif /* TINY_JSON_SERIALIZEABLE_H */
