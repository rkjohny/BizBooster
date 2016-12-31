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

#include "SessionManager.h"


#define MAX_SESSION_MANAGER_THREAD_SLEEP_IN_SEC 30

namespace Dal {


std::mutex SessionManager::m_mutex;
std::map<std::string, Session*> SessionManager::m_sessions;
volatile bool SessionManager::m_started = false;
SessionManager::Thread SessionManager::m_thread(&SessionManager::Cleanup);

bool SessionManager::IsValidToken(const std::string &token)
{
    bool ret = false;

    m_mutex.lock();
    auto itr = m_sessions.find(token);
    if (itr != m_sessions.end()) {
        ret = itr->second->IsExpired();
    }
    m_mutex.unlock();

    return ret;
}

void SessionManager::AddSession(const std::string &token, const Dal::User &user)
{
    m_mutex.lock();

    Session *session = new Session();
    session->SetUser(user);

    auto itr = m_sessions.find(token);
    if (itr != m_sessions.end()) {
        delete itr->second;
    }
    m_sessions[token] = session;

    m_mutex.unlock();
}

bool SessionManager::ResetExpiration(const std::string &token, uint64_t msec)
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

bool SessionManager::ResetExpiration(const std::string &token)
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

bool SessionManager::SetPinned(const std::string &token, volatile bool pinned)
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

Requester* SessionManager::GetRequetser(const std::string &token)
{
    Requester *requester = nullptr;

    m_mutex.lock();
    auto itr = m_sessions.find(token);
    if (itr != m_sessions.end()) {
        requester = itr->second->GetRequester();
    }
    m_mutex.unlock();

    return requester;
}

void SessionManager::Cleanup()
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
                    delete itr->second;
                    m_sessions.erase(itr);
                } else {
                    break;
                }
            }
        } catch (...) {
        }
        m_mutex.unlock();

        //30 seconds
        sleep(MAX_SESSION_MANAGER_THREAD_SLEEP_IN_SEC);
    }
}

void SessionManager::StartCleanUpThread()
{
    if (!m_started) {
        m_thread.Start();
    }
}

void SessionManager::StopCleanUpThread()
{
    m_started = false;
    m_thread.Join();
}

}