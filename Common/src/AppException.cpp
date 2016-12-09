
#include <Converter.h>
#include "AppException.h"


namespace Common {

AppException::AppException(const string& message) :
runtime_error(message.c_str())
{
    m_code = AppErrorCode::UN_KNOWN_ERROR;
    m_message = message;
}

AppException::AppException(AppErrorCode code, const string& message) :
runtime_error(message.c_str())
{
    m_code = code;
    m_message = message;
}

AppException::AppException(const AppException &e) :
runtime_error(e.GetMessage().c_str())
{
    m_code = e.GetCode();
    m_message = e.GetMessage();
}

AppException::AppException(const exception& e, const string& message) :
runtime_error(e.what() ? e.what() : message.c_str())
{
    m_code = AppErrorCode::UN_KNOWN_ERROR;
    SetMessage(e, message);
}

AppException::AppException(const exception& e, AppErrorCode code, const string& message) :
runtime_error(e.what() ? e.what() : message.c_str())
{
    m_code = code;
    SetMessage(e, message);
}

AppException::~AppException()
{
}

AppException& AppException::operator=(AppException& e)
{
    m_code = e.GetCode();
    m_message = e.GetMessage();
    return *this;
}

AppErrorCode AppException::GetCode() const
{
    return m_code;
}

string AppException::GetMessage() const
{
    return m_message;
}

string AppException::ToString() const
{
    string c = Converter::ToStr(static_cast<int> (m_code));
    string s = "ErrorCode: " + c + " ErrorMessage: " + m_message;
    return s;
}

void AppException::SetMessage(const exception& e, const string &message)
{
    if (message.compare("Unknown") != 0) {
        if (e.what()) {
            m_message = message + " Error: [" + e.what() + "]";
        }
    } else {
        if (e.what()) {
            m_message = e.what();
        }
    }
}

} /* namespace Common */
