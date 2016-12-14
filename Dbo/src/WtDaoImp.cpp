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

#include "WtDaoImp.h"
#include "DboDef.h"
#include "Converter.h"
#include "AppFactory.h"


namespace Dal {

std::shared_ptr<WtDaoImp>  WtDaoImp::m_instance = nullptr;

WtDaoImp::WtDaoImp() //:m_postgres("host=127.0.0.1 user=postgres password=1234 port=5432 dbname=biz_booster_db")
{
    /*
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

    m_postgres.connect(conn_string);
    m_postgres.setProperty("show-queries", "true");
    m_session.setConnection(m_postgres);

    m_session.mapClass<Dal::AppSetting>("t_setting");
    m_session.mapClass<Dal::User>("t_user");
    */
}

WtDaoImp::~WtDaoImp()
{
    //TODO: commit/rollback if pending, close the connection
    m_session.flush();
}

std::shared_ptr<WtDaoImp> WtDaoImp::GetInstance()
{
    if (WtDaoImp::m_instance == nullptr) {
        WtDaoImp::m_instance = std::shared_ptr<WtDaoImp>(new WtDaoImp());
    }
    return WtDaoImp::m_instance;
}

void WtDaoImp::CreateTables()
{
    m_session.createTables();
}

Wt::Dbo::Transaction WtDaoImp::BeginTransaction()
{
    return Wt::Dbo::Transaction(m_session);
}

bool WtDaoImp::CommitTransaction(Wt::Dbo::Transaction &transaction)
{
    //TODO: what will happen if this transaction is not the most recent transaction in the session?
    //      i.e, if commit returns false;
    bool commited = transaction.commit();
    return commited;
}

void WtDaoImp::RollbackTransaction(Wt::Dbo::Transaction& transaction)
{
   transaction.rollback();
}

bool WtDaoImp::TableExists(std::string table_name)
{
    auto transaction = this->BeginTransaction();
    int count = m_session.query<int>("SELECT count(1) FROM PG_CLASS").where("RELNAME = ?").bind(table_name);
    this->CommitTransaction(transaction);
    
    return (count > 0) ? true : false;
}

int WtDaoImp::GetNextDmVersion()
{
    int nextDmVersion = 0;

    auto transaction = this->BeginTransaction();
    try {
        Wt::Dbo::ptr<Dal::AppSetting> obj =
                m_session.find<Dal::AppSetting>().where("name = ?").bind(NEXT_DM_VERSION_KEY);
        if (obj) {
            std::string value = obj->GetValue();
            nextDmVersion = Common::Converter::ToInt32(std::move(value));
        }
    } catch (std::exception &e) {
        std::cout << e.what() << std::endl;
        nextDmVersion = 0;
    }
    this->CommitTransaction(transaction);

    return nextDmVersion;
}

void WtDaoImp::AddOrUpdateAppSetting(AppSetting &&setting)
{
    Wt::Dbo::Transaction transaction = this->BeginTransaction();
    Wt::Dbo::ptr<Dal::AppSetting> obj =
            m_session.find<Dal::AppSetting>().where("name = ?").bind(setting.GetName());
    if (!obj) {
        obj = m_session.add<AppSetting>(new AppSetting(std::string(setting.GetName())));
    }
    obj.modify()->SetValue(setting.GetValue());
    this->CommitTransaction(transaction);
}

Wt::Dbo::ptr<User> WtDaoImp::RegisterUser(User &loggedUser, User *user)
{
    return this->AddEnitity(user);
}

Wt::Dbo::ptr<User> WtDaoImp::GetUser(User &loggedUser, std::string email)
{
    Wt::Dbo::ptr<User> user;
    user = m_session.find<Dal::User>().where("email = ? and status = ?").bind(email).bind(Status::V);
    return user;
}


}


