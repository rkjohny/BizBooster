//
// Created by rezaul on 12/8/16.
//

#ifndef CONFIG_READER_H
#define CONFIG_READER_H

#include "AppDef.h"

namespace Common {

class ConfigReader : public SharedObject, public Disposable
{
public:
    virtual string GetValueOf(const string& key) = 0;

    virtual void ReloadFile() throw (AppException) = 0;

    virtual void SetFile(const string& fileName) throw (AppException) = 0;

protected:
    ConfigReader() = default;
    virtual ~ConfigReader() = default;

    NON_COPY_NON_ASSIGN_ABLE(ConfigReader);
};

}

#endif //CONFIG_READER_H
