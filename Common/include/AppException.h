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

#ifndef APP_EXCEPTION_H
#define APP_EXCEPTION_H

#include <string>
#include <stdexcept>
#include "AppError.h"
#include <cpprest/json.h>

namespace Common {
    
    class AppException : public std::runtime_error {
    public:        
        explicit AppException(const std::string& message = "Unknown");
        
        explicit AppException(AppErrorCode code, const std::string& message = "Unknown");

        AppException(const AppException &e);

        explicit AppException(const std::exception& e, const std::string& message = "Unknown");

        explicit AppException(const std::exception& e, AppErrorCode code, const std::string& message = "Unknown");
        
        
        
        explicit AppException(const std::string &&message = "Unknown");
        
        explicit AppException(AppErrorCode code, const std::string&& message = "Unknown");

        AppException(const AppException &&e);

        explicit AppException(const std::exception &&e, const std::string &&message = "Unknown");

        explicit AppException(const std::exception &&e, AppErrorCode code, const std::string &&message = "Unknown");

        
        virtual ~AppException();

        AppException& operator=(AppException &e);
        AppException& operator=(AppException &&e);

        AppErrorCode GetCode() const;

        const std::string& GetMessage() const;

        web::json::value Serialize() const;

        std::string ToString() const;

    private:
        AppErrorCode m_code;
        std::string m_message;

        void SetMessage(const std::exception &e, const std::string &message);
        void SetMessage(const std::exception &&e, const std::string &&message);
    };

} /* namespace Common */

#endif /* APP_EXCEPTION_H */
