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

#include "WtSession.h"
#include "CFReaderFactory.h"
#include "DboDef.h"
#include "AppSetting.h"


namespace Dal {

WtSession::WtSession()
{
    auto config_reader = Fio::CFReaderFactory::CreateConfigReader(
            DBO_CONFIG_FILE_NAME, Fio::ConFigFileType::PROPERTY_FILE);
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
    mapClass<Dal::AuthInfo>("t_auth_info");
    mapClass<Dal::AuthInfo::AuthIdentityType>("t_auth_identity");
    mapClass<Dal::AuthInfo::AuthTokenType>("t_auth_token");
}

WtSession::~WtSession()
{
    Dispose();
}

void WtSession::Dispose()
{
    if (!m_isDosposed) {
        m_connection.Dispose();
        //Just flush the session, we are not closing connection.
        this->flush();
        m_isDosposed = true;
    }
}

}