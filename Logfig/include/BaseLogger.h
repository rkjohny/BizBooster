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

#ifndef LOGFIG_BASE_LOGGER_H
#define LOGFIG_BASE_LOGGER_H

#include <map>
#include <string>
#include "SharedObject.h"
#include "Disposable.h"
#include "OStream.h"
#include "AppCommonDef.h"

namespace Logfig {
using namespace std;

class BaseLogger : public Common::SharedObject, public Common::Disposable {
private:
    NON_COPY_NON_MOVE_ABLE(BaseLogger);

    map<string, OStream *> m_streamList;
    int m_logLevel;   

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

    void AddStream(const string &key, OStream *ostram);

    void RemoveStream(const string &key);

    void Debug(const string &&prefix, const string &&message);
    void Info(const string &&prefix, const string &&message);
    void Warning(const string &&prefix, const string &&message);
    void Error(const string &&prefix, const string &&message);

    void Debug(const string &&prefix, const string &message);
    void Info(const string &&prefix, const string &message);
    void Warning(const string &&prefix, const string &message);
    void Error(const string &&prefix, const string &message);
    
    void Write(const string &&message);
    void Write(const string& message);

    int GetLogLevel();
};

} /* namespace Common */

#endif /* LOGFIG_BASE_LOGGER_H */
