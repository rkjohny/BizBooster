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

namespace Common {
using namespace std;

class BaseLogger: public SharedObject, public Disposable
{
private:

    enum LogLevel
    {
        LOG_LVEL_ERROR = 0,
        LOG_LEVEL_WARNING = 1,
        LOG_LEVEL_INFO = 2,
        LOG_LEVEL_DEBUG = 3
    };

    map< string, OStream* > m_streamList;
    int m_logLevel;

    BaseLogger( const BaseLogger& ) = delete;
    BaseLogger& operator=( const BaseLogger& ) = delete;

protected:
    BaseLogger();
    ~BaseLogger();

    void Dispose() override;

public:

    void SetLogLevel( int level );

    void AddStream( const string& key, OStream* ostram );

    void RemoveStream( const string& key );

    void Debug( const string& fname, const string& message );

    void Info( const string& fname, const string& message );

    void Warning( const string& fname, const string& message );

    void Error( const string& fname, const string& message );

    void Write( const string& message );
};

} /* namespace Common */

#endif /* BASELOGGER_H_ */
