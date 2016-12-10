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

#ifndef APP_EXCEPTION_H
#define APP_EXCEPTION_H

#include <string>
#include <stdexcept>
#include "AppError.h"

namespace Common {
    using namespace std;

    class AppException : public runtime_error {
    public:

        explicit AppException(const string& message = "Unknown");

        explicit AppException(AppErrorCode code, const string& message = "Unknown");

        AppException(const AppException &e);

        explicit AppException(const exception& e, const string& message = "Unknown");

        explicit AppException(const exception& e, AppErrorCode code, const string& message = "Unknown");

        virtual ~AppException();

        AppException& operator=(AppException& e);

        AppErrorCode GetCode() const;

        const string& GetMessage() const;

        string ToString() const;

    private:
        AppErrorCode m_code;
        string m_message;

        void SetMessage(const exception& e, const string &message);
    };

} /* namespace Common */

#endif /* APP_EXCEPTION_H */
