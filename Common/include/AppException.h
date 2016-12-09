/*
 * TradeXException.h
 *
 *  Created on: Oct 12, 2016
 *      Author: rezaul
 */

#ifndef APPEXCEPTION_H_
#define APPEXCEPTION_H_

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

        string GetMessage() const;

        string ToString() const;

    private:
        AppErrorCode m_code;
        string m_message;

        void SetMessage(const exception& e, const string &message);
    };

} /* namespace Common */

#endif /* APPEXCEPTION_H_ */
