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

#include "AppDef.h"
#include "SharedObject.h"
#include "Disposable.h"
#include "AppException.h"
#include <string>

namespace Fio {

enum ConFigFileType {
    PROPERTY_FILE,
    XML_FILE
};

class ConfigReader : public Common::SharedObject, public Common::Disposable {
public:
    virtual std::string GetValueOf(const std::string& key) = 0;

    virtual void ReloadFile() throw (Common::AppException) = 0;

    virtual void SetFile(const std::string& fileName) throw (Common::AppException) = 0;

    void SetType(ConFigFileType type);
    ConFigFileType GetType() const;
    
protected:

    ConfigReader(ConFigFileType type);
    virtual ~ConfigReader() = default;

    NON_COPY_NON_MOVE_ABLE(ConfigReader);

    ConFigFileType m_type;
};

}

#endif //CONFIG_READER_H
