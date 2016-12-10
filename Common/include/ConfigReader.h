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


#ifndef CONFIG_READER_H
#define CONFIG_READER_H

#include "AppConfig.h"

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
