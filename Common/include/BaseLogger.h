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

#ifndef BASE_LOGGER_H
#define BASE_LOGGER_H

#include <map>
#include <string>
#include "SharedObject.h"
#include "Disposable.h"
#include "OStream.h"
#include "AppConfig.h"

namespace Common {
using namespace std;

class BaseLogger : public SharedObject, public Disposable {
private:

    map<string, OStream *> m_streamList;
    int m_logLevel;

    NON_COPY_NON_ASSIGN_ABLE(BaseLogger);

protected:
    BaseLogger();

    virtual ~BaseLogger();

public:

    enum LogLevel {
        LOG_LEVEL_ERROR = 0,
        LOG_LEVEL_WARNING = 1,
        LOG_LEVEL_INFO = 2,
        LOG_LEVEL_DEBUG = 3
    };


    void Dispose() override;

    void SetLogLevel(int level);

    void AddStream(const string &&key, OStream *ostram);

    void RemoveStream(const string &&key);

    void Debug(const string &&prefix, const string &&message);

    void Info(const string &&prefix, const string &&message);

    void Warning(const string &&prefix, const string &&message);

    void Error(const string &&prefix, const string &&message);

    void Write(const string &&message);

    int GetLogLevel();
};

} /* namespace Common */

#endif /* BASE_LOGGER_H */
