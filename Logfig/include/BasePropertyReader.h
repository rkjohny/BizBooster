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

#ifndef LOGFIG_BASE_PROPERTY_READER_H
#define LOGFIG_BASE_PROPERTY_READER_H

#include <map>
#include <string>
#include "SharedObject.h"
#include "Disposable.h"
#include "AppException.h"
#include "AppCommonDef.h"
#include "ConfigReader.h"

namespace Logfig {
    using namespace std;

    class BasePropertyReader : public ConfigReader {
    private:
        NON_COPY_NON_MOVE_ABLE(BasePropertyReader);
        
        map< string, string > m_properties;
        string m_fileName;        
        
    public:
        string GetValueOf(const string& key) override;

        void ReloadFile() noexcept(false) override;

        void SetFile(const string& fileName) noexcept(false) override;

    protected:
        BasePropertyReader();
        virtual ~BasePropertyReader();

        void LoadFile(const string& fileName) noexcept(false);
        void Dispose() override;        
    };

} /* namespace Common */

#endif /* LOGFIG_BASE_PROPERTY_READER_H */
