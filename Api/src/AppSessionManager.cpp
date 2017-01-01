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

#include "AppSessionManager.h"
#include "DboDef.h"


namespace Api {

std::mutex AppSessionManager::m_mutex;
std::map<std::string, std::shared_ptr<AppSession>> AppSessionManager::m_sessions;
volatile bool AppSessionManager::m_started = false;
AppSessionManager::Thread AppSessionManager::m_thread(&AppSessionManager::Cleanup);

bool AppSessionManager::IsValidToken(const std::string &token)
{
    bool ret = false;

    m_mutex.lock();
    auto itr = m_sessions.find(token);
    if (itr != m_sessions.end()) {
        ret = !itr->second->IsExpired();
    }
    m_mutex.unlock();

    return ret;
}

void AppSessionManager::AddSession(const std::string &token, const Dal::User &user)
{
    bool is_pinned = false;

    m_mutex.lock();

    std::shared_ptr<AppSession> session = std::shared_ptr<AppSession>(new AppSession());
    session->SetUser(user);

    auto itr = m_sessions.find(token);
    if (itr != m_sessions.end()) {
        //delete itr->second;
        is_pinned = itr->second->IsPinned();
        if (!is_pinned) {
            m_sessions.erase(itr);
        }
    }
    if (!is_pinned) {
        m_sessions[token] = session;
    }

    m_mutex.unlock();
}

void AppSessionManager::AddSession(const std::string &token, const Dal::User &user, uint64_t expiresMsc)
{
    bool is_pinned = false;
    
    m_mutex.lock();

    std::shared_ptr<AppSession> session = std::shared_ptr<AppSession>(new AppSession());
    session->SetUser(user);
    session->ResetExpiration(expiresMsc);

    auto itr = m_sessions.find(token);
    if (itr != m_sessions.end()) {
        //delete itr->second;
        is_pinned = itr->second->IsPinned();
        if (!is_pinned) {
            m_sessions.erase(itr);
        }
    }
    if (!is_pinned) {
        m_sessions[token] = session;
    }

    m_mutex.unlock();
}

bool AppSessionManager::ResetExpiration(const std::string &token, uint64_t msec)
{
    bool ret = false;

    m_mutex.lock();
    auto itr = m_sessions.find(token);
    if (itr != m_sessions.end()) {
        itr->second->ResetExpiration(msec);
        ret = true;
    }
    m_mutex.unlock();

    return ret;
}

bool AppSessionManager::ResetExpiration(const std::string &token)
{
    bool ret = false;

    m_mutex.lock();
    auto itr = m_sessions.find(token);
    if (itr != m_sessions.end()) {
        itr->second->ResetExpiration(DEFAULT_SESSION_TIME_OUT);
        ret = true;
    }
    m_mutex.unlock();

    return ret;
}

bool AppSessionManager::SetPinned(const std::string &token, volatile bool pinned)
{
    bool ret = false;

    m_mutex.lock();
    auto itr = m_sessions.find(token);
    if (itr != m_sessions.end()) {
        itr->second->SetPinned(pinned);
        ret = true;
    }
    m_mutex.unlock();

    return ret;
}

std::weak_ptr<AppSession> AppSessionManager::GetSession(const std::string &token)
{
    std::weak_ptr<AppSession> session;
    
    m_mutex.lock();
    auto itr = m_sessions.find(token);
    if (itr != m_sessions.end()) {
        //itr->second->SetPinned(true);
        session = itr->second;
    }
    m_mutex.unlock();
    
    return session;
}

std::weak_ptr<Dal::AuthenticatedRequester> AppSessionManager::GetRequetser(const std::string &token)
{
    std::weak_ptr<Dal::AuthenticatedRequester> requester;

    m_mutex.lock();
    auto itr = m_sessions.find(token);
    if (itr != m_sessions.end()) {
        //itr->second->SetPinned(true);
        requester = itr->second->GetRequester();
    }
    m_mutex.unlock();

    return requester;
}

void AppSessionManager::Cleanup()
{
    m_started = true;

    while (m_started) {
        m_mutex.lock();
        try {
            while (m_started) {
                auto itr = m_sessions.begin();
                for (; itr != m_sessions.end(); ++itr) {
                    if (!itr->second->IsPinned()) {
                        if (itr->second->IsExpired()) {
                            break;
                        }
                    }
                }
                if (itr != m_sessions.end()) {
                    //delete itr->second;
                    m_sessions.erase(itr);
                } else {
                    break;
                }
            }
        } catch (...) {
        }
        m_mutex.unlock();

        sleep(MAX_SESSION_MANAGER_THREAD_SLEEP_IN_SEC);
    }
}

void AppSessionManager::StartCleanUpThread()
{
    if (!m_started) {
        m_thread.Start();
    }
}

void AppSessionManager::StopCleanUpThread()
{
    m_started = false;
    m_thread.Join();
}

}