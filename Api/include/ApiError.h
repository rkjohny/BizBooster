/**
 * ApiError.h
 *
 *      Author: rezaul
 *
 * Copyright (C) 2016 Rezaul Karim, rkjohny@gmail.com. All rights reserved.
 */

#ifndef APIERROR_H_
#define APIERROR_H_

#include <string>
#include "Json.h"
#include "SerializableT.h"

namespace Api {
    using namespace std;

    class ApiError : public Json::SerializableT<ApiError> {
    public:
        ApiError();

        void SetCode(int code);
        void SetMessage(const string& message);
        int GetCode() const;
        const string& GetMessage() const;

        REGISTER_GETTER_INCLUDING_BASE_START(Json::SerializableT<ApiError>)
        GETTER(ApiError, int, "code", &ApiError::GetCode),
        GETTER(ApiError, const string&, "message", &ApiError::GetMessage)
        REGISTER_GETTER_INCLUDING_BASE_END


        REGISTER_SETTER_INCLUDING_BASE_START(Json::SerializableT<ApiError>)
        SETTER(ApiError, int, "code", &ApiError::SetCode),
        SETTER(ApiError, const string&, "message", &ApiError::SetMessage)
        REGISTER_SETTER_INCLUDING_BASE_END

    private:
        int m_code;
        string m_message;
    };

} /* namespace Api */

#endif /* APIERROR_H_ */
