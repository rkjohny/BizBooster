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

#include "BaseService.h"
#include <Requester.h>
#include <Converter.h>
#include "LoggerFactory.h"

namespace Cruxdb {

    BaseService *BaseService::m_instance = nullptr;

    BaseService *BaseService::GetInstance()
    {
        if (!m_instance) {
            m_instance = new BaseService();
        }
        return m_instance;
    }

    BaseService::BaseService()
    {
        m_session = WtSession::GetInstance();
    }

    BaseService::~BaseService() {
        Dispose();
    }

    void BaseService::Dispose()
    {
        //     if (!m_isDosposed) {
        //        //TODO: commit/rollback if pending, close the connection
        //         m_session->Dispose();
        //         m_isDosposed = true;
        //     }

        //Just flush the session, we are not closing connection.
        m_session->flush();
    }

    void BaseService::CreateTables(Requester *requester)
    {
        try {
            LOG_INFO("Creating Tables...");
            m_session->createTables();
        } catch (std::exception &e) {
            LOG_DEBUG(std::string("Ignoring: ") + e.what())
            LOG_INFO("Table already exists and will not be created.");
        }
    }

    int BaseService::GetNextDmVersion(Requester *requester)
    {
        int nextDmVersion = 0;

        try {
            auto query = m_session->find<Cruxdb::AppSetting>().where("name = ?").bind(NEXT_DM_VERSION_KEY);
            auto appSettingsPtr = query.resultValue();
            if (appSettingsPtr) {
                auto value = appSettingsPtr->GetValue();
                nextDmVersion = Common::Converter::ToInt32(value);
            }
        } catch (std::exception &e) {
            nextDmVersion = 0;
        }
        return nextDmVersion;
    }

    Wt::Dbo::Transaction BaseService::BeginTransaction(Requester *requester)
    {
        return Wt::Dbo::Transaction(*m_session);
    }

    bool BaseService::CommitTransaction(Requester *requester, Wt::Dbo::Transaction& transaction)
    {
        //TODO: what will happen if this transaction is not the most recent transaction in the session?
        //      i.e, if commit returns false;
        bool commited = transaction.commit();
        return commited;
    }

    void BaseService::RollbackTransaction(Requester *requester, Wt::Dbo::Transaction& transaction)
    {
        transaction.rollback();
    }

    bool BaseService::TableExists(Requester *requester, const std::string &table_name)
    {
        auto count = m_session->query<int>("SELECT count(1) FROM PG_CLASS").where("RELNAME = ?").bind(table_name);
        return (count > 0) ? true : false;
    }

}

