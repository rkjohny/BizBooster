/**
 * ApiError.h
 *
 *      Author: rezaul
 *
 * Copyright (C) 2016 Rezaul Karim, rkjohny@gmail.com. All rights reserved.
 */

#ifndef API_ERROR_H
#define API_ERROR_H

#include <string>
#include "Json.h"
#include "SerializableT.h"
#include "AppError.h"

namespace Api {
    using namespace std;

    class ApiError : public Json::SerializableT<ApiError> {
    public:
        ApiError();
        ApiError(AppErrorCode code, const std::string &message);

        void SetCode(AppErrorCode code);
        void SetMessage(const string& message);
        AppErrorCode GetCode() const;
        const string& GetMessage() const;

        REGISTER_GETTER_INCLUDING_BASE_START(Json::SerializableT<ApiError>)
        GETTER(ApiError, AppErrorCode, "code", &ApiError::GetCode),
        GETTER(ApiError, const string&, "message", &ApiError::GetMessage)
        REGISTER_GETTER_INCLUDING_BASE_END


        REGISTER_SETTER_INCLUDING_BASE_START(Json::SerializableT<ApiError>)
        SETTER(ApiError, AppErrorCode, "code", &ApiError::SetCode),
        SETTER(ApiError, const string&, "message", &ApiError::SetMessage)
        REGISTER_SETTER_INCLUDING_BASE_END

    private:
        AppErrorCode m_code;
        string m_message;
    };

} /* namespace Api */

#endif /* API_ERROR_H */
