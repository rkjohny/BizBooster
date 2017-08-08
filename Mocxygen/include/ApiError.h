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

#ifndef API_ERROR_H
#define API_ERROR_H

#include <string>
#include "Json.h"
#include "SerializableT.h"
#include "AppError.h"
#include "AppException.h"
#include "AppCommonDef.h"


namespace Mocxygen {

class ApiError : public Cmarshal::Json::SerializableT<ApiError> {
public:
    SERIALIZEABLE(ApiError);
    
    ApiError(AppErrorCode code, const std::string &message);

    void SetCode(AppErrorCode code);
    void SetMessage(const std::string& message);
    void SetError(AppErrorCode code, const std::string &message);
    void SetError(const ApiError &error);
    void SetError(ApiError &&error);

    void SetError(Common::AppException &e);
    void SetError(Common::AppException &&e);
    ApiError& operator=(Common::AppException &e);
    ApiError& operator=(Common::AppException &&e);

    void SetError(std::exception &e);
    void SetError(std::exception &&e);
    ApiError& operator=(std::exception &e);
    ApiError& operator=(std::exception &&e);

    AppErrorCode GetCode() const;
    const std::string& GetMessage() const;

    web::json::value Serialize() const;
    std::string ToString() const;

    REGISTER_GETTER_INCLUDING_BASE_START(Cmarshal::Json::SerializableT<ApiError>)
    GETTER(ApiError, AppErrorCode, "code", &ApiError::GetCode),
    GETTER(ApiError, const std::string&, "message", &ApiError::GetMessage)
    REGISTER_GETTER_INCLUDING_BASE_END


    REGISTER_SETTER_INCLUDING_BASE_START(Cmarshal::Json::SerializableT<ApiError>)
    SETTER(ApiError, AppErrorCode, "code", &ApiError::SetCode),
    SETTER(ApiError, const std::string&, "message", &ApiError::SetMessage)
    REGISTER_SETTER_INCLUDING_BASE_END

private:
    AppErrorCode m_code;
    std::string m_message;
};

} /* namespace Mocxygen */

#endif /* API_ERROR_H */
