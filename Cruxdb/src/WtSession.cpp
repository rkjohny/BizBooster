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

#include "WtSession.h"
#include "CFReaderFactory.h"
#include "CruxdbDef.h"
#include "AppSetting.h"
#include "AuthServices.h"


namespace Cruxdb {

WtSession *WtSession::m_instance = nullptr;;

WtSession::WtSession()
{
    auto config_reader = Logfig::CFReaderFactory::CreateConfigReader(
            DBO_CONFIG_FILE_NAME, Logfig::ConFigFileType::PROPERTY_FILE);
    config_reader->SetFile(DBO_CONFIG_FILE_NAME);

    auto db_host = config_reader->GetValueOf(DB_HOST);
    auto db_name = config_reader->GetValueOf(DB_NAME);
    auto db_user_name = config_reader->GetValueOf(DB_USER_NAME);
    auto db_user_pass = config_reader->GetValueOf(DB_USER_PASSWORD);

    auto conn_string = "host=" + db_host + " user=" + db_user_name +
            " password=" + db_user_pass + " dbname=" + db_name;

    std::cout << conn_string << std::endl;

    m_connection.connect(conn_string);
    m_connection.setProperty("show-queries", "true");

    setConnection(m_connection);

    mapClass<Cruxdb::AppSetting>("setting");
    mapClass<Cruxdb::User>("user");
    mapClass<Cruxdb::AuthInfo>("auth_info");
    mapClass<Cruxdb::AuthInfo::AuthIdentityType>("auth_identity");
    mapClass<Cruxdb::AuthInfo::AuthTokenType>("auth_token");
    
    m_users = std::make_shared<Cruxdb::UserDatabase>(*this, &AuthServices::GetAuthService());
}

WtSession* WtSession::GetInstance()
{
    if (!m_instance) {
        m_instance = new WtSession();
    }
    return m_instance;
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

Cruxdb::UserDatabase& WtSession::GetUserDB()
{
    return *m_users;
}

}