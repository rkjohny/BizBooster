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


#ifndef APP_FACTORY_H
#define APP_FACTORY_H

#include "BasePropertyReader.h"
#include <memory>
#include <map>


namespace Fio {

class CFReaderFactory {
public:    

    class PropertyReader : public BasePropertyReader {
        friend class CFReaderFactory;

    protected:
        ~PropertyReader() = default;
        PropertyReader() = default;

        NON_COPY_NON_MOVE_ABLE(PropertyReader);
    };

    static void Dispose();

    static ConfigReader* CreateConfigReader(std::string &&key, ConFigFileType type);
    static ConfigReader* GetConfigReader(std::string &&key);
    static bool DisposeConfigReader(std::string &&key);
    static void DisposeConfigReader();

private:
    MAKE_STATIC(CFReaderFactory);

    static std::map<std::string, ConfigReader*> cm_configReaderList;
};

} /* namespace Common */

#endif /* APP_FACTORY_H */
