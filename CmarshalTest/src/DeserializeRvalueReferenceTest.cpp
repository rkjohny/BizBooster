//
// Created by rezaul on 11/28/16.
//

#include <gtest/gtest.h>
#include <cpprest/json.h>
#include <string>
#include "Json.h"

namespace CmarshalTest {
    namespace JsonTest {
        namespace TestDeserializer {

            class RvalueReference {
            public:
                int id;
                std::string name;

                void SetId(int &&id) {
                    this->id = id;
                }

                void SetName(const std::string &&name) {
                    this->name = name;
                }

            REGISTER_SETTER_START
                SETTER(RvalueReference, int &&, "id", &RvalueReference::SetId),
                SETTER(RvalueReference, const std::string&&, "name", &RvalueReference::SetName)
                REGISTER_SETTER_END
            };

            TEST(RvalueReferenceTest, TestDeserialize) {
                web::json::value jvalue = web::json::value::object();
                jvalue[U("id")] = web::json::value(10);
                jvalue[U("name")] = web::json::value(U("Rezaul Karim"));

                RvalueReference obj;
                Cmarshal::Json::FromJson(obj, jvalue);
                ASSERT_TRUE(obj.id == 10);
                ASSERT_TRUE(obj.name.compare("Rezaul Karim") == 0);
            }
        }
    }
}