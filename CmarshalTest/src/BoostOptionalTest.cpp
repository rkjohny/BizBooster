/*
 * Copyright (C) 2017 Rezaul Karim (rkjohny@gmail.com)
 *     The information contained here-in is the property of Rezaul Karim and
 *     is not to be disclosed or used without prior written permission of Rezaul Karim.
 *     This copyright extends to all media in which this information may be preserved
 *     including magnetic storage, computer print-out or visual display.
 *     Please refer to License.txt file for more details.
 */


#include <gtest/gtest.h>
#include <cpprest/json.h>
#include "Json.h"

namespace CmarshalTest {
    namespace JsonTest {
        class Person {
        public:

            virtual ~Person() {
                delete *address;
                delete *ratePerHour;
                delete *review;
                delete *isAvailable;

                for (auto p : *blogs) {
                    delete p;
                }
            }

            const boost::optional<std::string> &GetName() const {
                return name;
            }

            void SetName(const boost::optional<std::string> &name) {
                Person::name = name;
            }

            const boost::optional<double> &GetScore() const {
                return score;
            }

            void SetScore(const boost::optional<double> &score) {
                Person::score = score;
            }

            const boost::optional<int> &GetAge() const {
                return age;
            }

            void SetAge(const boost::optional<int> &age) {
                Person::age = age;
            }

            const boost::optional<bool> &IsValid() const {
                return isValid;
            }

            void SetIsValid(const boost::optional<bool> &isValid) {
                Person::isValid = isValid;
            }

            const boost::optional<std::string *> &GetAddress() const {
                return address;
            }

            void SetAddress(const boost::optional<std::string *> &address) {
                Person::address = address;
            }

            const boost::optional<double *> &GetRatePerHour() const {
                return ratePerHour;
            }

            void SetRatePerHour(const boost::optional<double *> &ratePerHour) {
                Person::ratePerHour = ratePerHour;
            }

            const boost::optional<int *> &GetReview() const {
                return review;
            }

            void SetReview(const boost::optional<int *> &review) {
                Person::review = review;
            }

            const boost::optional<bool *> &IsAvailable() const {
                return isAvailable;
            }

            void SetIsAvailable(const boost::optional<bool *> &isAvailable) {
                Person::isAvailable = isAvailable;
            }

            const boost::optional<std::vector<std::string>> &GetComments() const {
                return comments;
            }

            void SetComments(const boost::optional<std::vector<std::string>> &comments) {
                Person::comments = comments;
            }

            const boost::optional<std::vector<std::string *>> &GetBlogs() const {
                return blogs;
            }

            void SetBlogs(const boost::optional<std::vector<std::string *>> &blogs) {
                Person::blogs = blogs;
            }

        REGISTER_GETTER_START
            GETTER(Person, const boost::optional<double> &, "score", &Person::GetScore),
            GETTER(Person, const boost::optional<bool> &, "isValid", &Person::IsValid),
            GETTER(Person, const boost::optional<std::string> &, "name", &Person::GetName),
            GETTER(Person, const boost::optional<int> &, "age", &Person::GetAge),
            GETTER(Person, const boost::optional<double *> &, "ratePerHour", &Person::GetRatePerHour),
            GETTER(Person, const boost::optional<bool *> &, "isAvailable", &Person::IsAvailable),
            GETTER(Person, const boost::optional<std::string *> &, "address", &Person::GetAddress),
            GETTER(Person, const boost::optional<int *> &, "review", &Person::GetReview),
            GETTER(Person, const boost::optional<std::vector<std::string>> &, "comments", &Person::GetComments),
            GETTER(Person, const boost::optional<std::vector<std::string *>> &, "blogs", &Person::GetBlogs)
            REGISTER_GETTER_END

        REGISTER_SETTER_START
            SETTER(Person, const boost::optional<double> &, "score", &Person::SetScore),
            SETTER(Person, const boost::optional<bool> &, "isValid", &Person::SetIsValid),
            SETTER(Person, const boost::optional<std::string> &, "name", &Person::SetName),
            SETTER(Person, const boost::optional<int> &, "age", &Person::SetAge),
            SETTER(Person, const boost::optional<double *> &, "ratePerHour", &Person::SetRatePerHour),
            SETTER(Person, const boost::optional<bool *> &, "isAvailable", &Person::SetIsAvailable),
            SETTER(Person, const boost::optional<std::string *> &, "address", &Person::SetAddress),
            SETTER(Person, const boost::optional<int *> &, "review", &Person::SetReview),
            SETTER(Person, const boost::optional<std::vector<std::string>> &, "comments", &Person::SetComments),
            SETTER(Person, const boost::optional<std::vector<std::string *>> &, "blogs", &Person::SetBlogs)
            REGISTER_SETTER_END

        private:
            boost::optional<std::string> name;
            boost::optional<double> score;
            boost::optional<int> age;
            boost::optional<bool> isValid;


            boost::optional<std::string *> address;
            boost::optional<double *> ratePerHour;
            boost::optional<int *> review;
            boost::optional<bool *> isAvailable;

            boost::optional<std::vector<std::string>> comments;
            boost::optional<std::vector<std::string *>> blogs;
        };


        TEST(DseralizePrimitive, IntegerType) {
            boost::optional<int> obj = boost::none;
            web::json::value jval = web::json::value::number(10);
            Cmarshal::Json::FromJson(obj, jval);
            ASSERT_TRUE(obj != boost::none);
            ASSERT_TRUE(obj.value() == 10);

            boost::optional<int *> objPointer = boost::none;
            web::json::value jvalPointer = web::json::value::number(10);
            Cmarshal::Json::FromJson(objPointer, jvalPointer);
            ASSERT_TRUE(obj != boost::none);
            ASSERT_TRUE(*(objPointer.value()) == 10);

            delete *objPointer;
        }

        TEST(SeralizePrimitive, IntegerType) {
            boost::optional<int> obj = 10;
            web::json::value jval = Cmarshal::Json::ToJson(obj);
            ASSERT_TRUE(jval.as_integer() == 10);

            boost::optional<int *> objPointer = new int(10);
            web::json::value jvalPointer = Cmarshal::Json::ToJson(objPointer);
            ASSERT_TRUE(jvalPointer.as_integer() == 10);

            delete *objPointer;
        }

        TEST(DseralizeObject, personType) {
            Person p;
            web::json::value jvalPerson;
            jvalPerson[U("name")] = web::json::value::string(utility::string_t("Rezaul"));
            jvalPerson[U("age")] = web::json::value::number(30);
            jvalPerson[U("score")] = web::json::value::number(25.78);
            jvalPerson[U("isValid")] = web::json::value::boolean(true);


            jvalPerson[U("address")] = web::json::value::string(utility::string_t("Dhaka"));
            jvalPerson[U("review")] = web::json::value::number(5);
            jvalPerson[U("ratePerHour")] = web::json::value::number(35.50);
            jvalPerson[U("isAvailable")] = web::json::value::boolean(true);

            web::json::value comments = web::json::value::array();
            web::json::array &arrayComments = comments.as_array();
            arrayComments[0] = web::json::value::string(utility::string_t("Good"));
            arrayComments[1] = web::json::value::string(utility::string_t("Average"));
            arrayComments[2] = web::json::value::string(utility::string_t("Excellent"));
            jvalPerson[U("comments")] = comments;

            web::json::value blogs = web::json::value::array();
            web::json::array &arrayBlogs = blogs.as_array();
            arrayBlogs[0] = web::json::value::string(utility::string_t("This is my first day at work"));
            arrayBlogs[1] = web::json::value::string(utility::string_t("I experienced an exciting thing"));
            arrayBlogs[2] = web::json::value::string(utility::string_t("I have done this!"));
            jvalPerson[U("blogs")] = blogs;

            Cmarshal::Json::FromJson(p, jvalPerson);

            ASSERT_TRUE((*p.GetName()).compare("Rezaul") == 0);
            ASSERT_TRUE((*p.GetScore()) == 25.78);
            ASSERT_TRUE((*p.GetAge()) == 30);
            ASSERT_TRUE((*p.IsValid()) == true);


            ASSERT_TRUE((*(*p.GetAddress())).compare("Dhaka") == 0);
            ASSERT_TRUE(*((*p.GetRatePerHour())) == 35.50);
            ASSERT_TRUE(*((*p.GetReview())) == 5);
            ASSERT_TRUE(*((*p.IsAvailable())) == true);

            std::vector<std::string> vComments = *p.GetComments();
            ASSERT_TRUE(vComments.at(0).compare("Good") == 0);
            ASSERT_TRUE(vComments.at(1).compare("Average") == 0);
            ASSERT_TRUE(vComments.at(2).compare("Excellent") == 0);

            std::vector<std::string*> vBlogs = *p.GetBlogs();
            ASSERT_TRUE(vBlogs.at(0)->compare("This is my first day at work") == 0);
            ASSERT_TRUE(vBlogs.at(1)->compare("I experienced an exciting thing") == 0);
            ASSERT_TRUE(vBlogs.at(2)->compare("I have done this!") == 0);
        }


        TEST(SeralizeObject, personType) {
            Person p;

            p.SetName(boost::optional<std::string>("Rezaul"));
            p.SetAge(boost::optional<int>(30));
            p.SetScore(boost::optional<double>(25.78));
            p.SetIsValid(boost::optional<bool>(true));
            p.SetAddress(new std::string("Dhaka"));
            p.SetReview(new int(5));
            p.SetRatePerHour(new double(35.50));
            p.SetIsAvailable(new bool(true));

            std::vector<std::string> comments;
            comments.push_back("Good");
            comments.push_back("Average");
            comments.push_back("Excellent");
            p.SetComments(comments);

            std::vector<std::string*> blogs;
            blogs.push_back(new std::string("This is my first day at work"));
            blogs.push_back(new std::string("I experienced an exciting thing"));
            blogs.push_back(new std::string("I have done this!"));
            p.SetBlogs(blogs);

            web::json::value jvalPerson = Cmarshal::Json::ToJson(p);

            ASSERT_TRUE(jvalPerson[U("name")] == web::json::value::string(utility::string_t("Rezaul")));
            ASSERT_TRUE(jvalPerson[U("age")] == web::json::value::number(30));
            ASSERT_TRUE(jvalPerson[U("score")] == web::json::value::number(25.78));
            ASSERT_TRUE(jvalPerson[U("isValid")] == web::json::value::boolean(true));

            ASSERT_TRUE(jvalPerson[U("address")] == web::json::value::string(utility::string_t("Dhaka")));
            ASSERT_TRUE(jvalPerson[U("review")] == web::json::value::number(5));
            ASSERT_TRUE(jvalPerson[U("ratePerHour")] == web::json::value::number(35.50));
            ASSERT_TRUE(jvalPerson[U("isAvailable")] == web::json::value::boolean(true));

            web::json::value jcomments = jvalPerson[U("comments")];
            ASSERT_TRUE(jcomments.is_array());
            web::json::array &arrComments = jcomments.as_array();
            ASSERT_TRUE(arrComments[0].as_string().compare("Good") == 0);
            ASSERT_TRUE(arrComments[1].as_string().compare("Average") == 0);
            ASSERT_TRUE(arrComments[2].as_string().compare("Excellent") == 0);

            web::json::value jblogs = jvalPerson[U("blogs")];
            ASSERT_TRUE(jblogs.is_array());
            web::json::array &arrBlogs = jblogs.as_array();
            ASSERT_TRUE(arrBlogs[0].as_string().compare("This is my first day at work") == 0);
            ASSERT_TRUE(arrBlogs[1].as_string().compare("I experienced an exciting thing") == 0);
            ASSERT_TRUE(arrBlogs[2].as_string().compare("I have done this!") == 0);
        }

    }
}

