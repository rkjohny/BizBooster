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

#ifndef SESSION_H
#define SESSION_H

#include "AppFactory.h"
#include "DboConfig.h"
#include "AppSetting.h"

#include <Wt/Dbo/Dbo>

namespace Dal {

template <class Conn>
class WtSession : public Wt::Dbo::Session {
public:
    WtSession() 
    {
        auto config_reader = Common::AppFactory::CreateConfigReader(
            DBO_CONFIG_FILE_NAME, Common::ConFigFileType::PROPERTY_FILE);
        config_reader->SetFile(DBO_CONFIG_FILE_NAME);

        std::string db_host = config_reader->GetValueOf(DB_HOST);
        std::string db_name = config_reader->GetValueOf(DB_NAME);
        std::string db_user_name = config_reader->GetValueOf(DB_USER_NAME);
        std::string db_user_pass = config_reader->GetValueOf(DB_USER_PASSWORD);

        std::string conn_string = "host=" + db_host + " user=" + db_user_name +
                                  " password=" + db_user_pass + " dbname=" + db_name;

        std::cout << conn_string << std::endl;

        m_connection.connect(conn_string);
        m_connection.setProperty("show-queries", "true");

        setConnection(m_connection);

        mapClass<Dal::AppSetting>("t_setting");
        mapClass<Dal::User>("t_user");
    }
    
    virtual ~WtSession()
    {
        
    }
    
private:
    Conn m_connection;
    
    WtSession(const WtSession& orig);
};

}

#endif /* SESSION_H */

