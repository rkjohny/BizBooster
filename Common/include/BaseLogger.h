/*
 * TradeXLogger.h
 *
 *  Created on: Oct 12, 2016
 *      Author: rezaul
 */

#ifndef BASELOGGER_H_
#define BASELOGGER_H_

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
    enum LogLevel {
        LOG_LVEL_ERROR = 0,
        LOG_LEVEL_WARNING = 1,
        LOG_LEVEL_INFO = 2,
        LOG_LEVEL_DEBUG = 3
    };

    map<string, OStream *> m_streamList;
    int m_logLevel;

    NON_COPY_NON_ASSIGN_ABLE(BaseLogger);

protected:
    BaseLogger();

    virtual ~BaseLogger();

public:

    void Dispose() override;

    void SetLogLevel(int level);

    void AddStream(const string &&key, OStream *ostram);

    void RemoveStream(const string &&key);

    void Debug(const string &&prefix, const string &&message);

    void Info(const string &&prefix, const string &&message);

    void Warning(const string &&prefix, const string &&message);

    void Error(const string &&prefix, const string &&message);

    void Write(const string &&message);
};

} /* namespace Common */

#endif /* BASELOGGER_H_ */
