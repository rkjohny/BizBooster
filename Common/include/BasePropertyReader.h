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

#ifndef BASE_PROPERTY_READER_H
#define BASE_PROPERTY_READER_H

#include <map>
#include <string>
#include "SharedObject.h"
#include "Disposable.h"
#include "AppException.h"
#include "AppDef.h"
#include "ConfigReader.h"

namespace Common {
    using namespace std;

    class BasePropertyReader : public ConfigReader {
    public:
        string GetValueOf(const string& key) override;

        void ReloadFile() throw (AppException) override;

        void SetFile(const string& fileName) throw (AppException) override;

    protected:
        BasePropertyReader();
        virtual ~BasePropertyReader();

        void LoadFile(const string& fileName) throw (AppException);
        void Dispose() override;

    private:
        map< string, string > m_properties;
        string m_fileName;

        NON_COPY_NON_MOVE_ABLE(BasePropertyReader);
    };

} /* namespace Common */

#endif /* BASE_PROPERTY_READER_H */
