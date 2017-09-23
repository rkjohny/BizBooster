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

#include "AppSessionManager.h"
#include "CruxdbDef.h"

namespace Mocxygen {

std::map<std::string, std::shared_ptr<AppSession>> AppSessionManager::cm_sessions;
boost::mutex AppSessionManager::cm_mutex;
boost::atomic<bool> AppSessionManager::cm_started(true);
boost::thread AppSessionManager::cm_thread(&AppSessionManager::Cleanup);

bool AppSessionManager::IsValidToken(const std::string &token)
{
    bool ret = false;
    
    boost::lock_guard<boost::mutex> guard(cm_mutex);

    auto itr = cm_sessions.find(token);
    if (itr != cm_sessions.end()) {
        ret = !itr->second->IsExpired();
    }
    return ret;
}

void AppSessionManager::AddSession(const std::string &token, Wt::Dbo::ptr<Cruxdb::User> &user)
{
    bool is_pinned = false;
    
    boost::lock_guard<boost::mutex> guard(cm_mutex);

    auto session = std::shared_ptr<AppSession>(new AppSession());
    session->SetUser(user);

    auto itr = cm_sessions.find(token);
    if (itr != cm_sessions.end()) {
        //delete itr->second;
        is_pinned = itr->second->IsPinned();
        if (!is_pinned) {
            cm_sessions.erase(itr);
        }
    }
    if (!is_pinned) {
        cm_sessions[token] = session;
    }
}

void AppSessionManager::AddSession(const std::string &token, Wt::Dbo::ptr<Cruxdb::User> &user, uint64_t expiresMsc)
{
    bool is_pinned = false;
    auto session = std::shared_ptr<AppSession>(new AppSession());
    session->SetUser(user);
    session->ResetExpiration(expiresMsc);
    
    boost::lock_guard<boost::mutex> guard(cm_mutex);

    auto itr = cm_sessions.find(token);
    if (itr != cm_sessions.end()) {
        is_pinned = itr->second->IsPinned();
        if (!is_pinned) {
            cm_sessions.erase(itr);
        }
    }
    if (!is_pinned) {
        cm_sessions[token] = session;
    }
}

bool AppSessionManager::ResetExpiration(const std::string &token, uint64_t msec)
{
    bool ret = false;

    boost::lock_guard<boost::mutex> guard(cm_mutex);

    auto itr = cm_sessions.find(token);
    if (itr != cm_sessions.end()) {
        itr->second->ResetExpiration(msec);
        ret = true;
    }
    return ret;
}

bool AppSessionManager::ResetExpiration(const std::string &token)
{
    bool ret = false;
    
    boost::lock_guard<boost::mutex> guard(cm_mutex);
    
    auto itr = cm_sessions.find(token);
    if (itr != cm_sessions.end()) {
        itr->second->ResetExpiration(DEFAULT_SESSION_TIME_OUT_IN_SEC);
        ret = true;
    }
   return ret;
}

bool AppSessionManager::SetPinned(const std::string &token, volatile bool pinned)
{
    bool ret = false;

    boost::lock_guard<boost::mutex> guard(cm_mutex);
    
    auto itr = cm_sessions.find(token);
    if (itr != cm_sessions.end()) {
        itr->second->SetPinned(pinned);
        ret = true;
    }
    return ret;
}

std::weak_ptr<AppSession> AppSessionManager::GetSession(const std::string &token)
{
    std::weak_ptr<AppSession> session;
        
    boost::lock_guard<boost::mutex> guard(cm_mutex);
    
    auto itr = cm_sessions.find(token);
    if (itr != cm_sessions.end()) {
        session = itr->second;
    }
    return session;
}

std::weak_ptr<Cruxdb::AuthenticatedRequester> AppSessionManager::GetRequetser(const std::string &token)
{
    std::weak_ptr<Cruxdb::AuthenticatedRequester> requester;

    boost::lock_guard<boost::mutex> guard(cm_mutex);
    
    auto itr = cm_sessions.find(token);
    if (itr != cm_sessions.end()) {
        requester = itr->second->GetRequester();
    }
    return requester;
}

void AppSessionManager::Cleanup()
{
    while (cm_started) {
        {
            boost::lock_guard<boost::mutex> guard(cm_mutex);
            try {
                while (cm_started) {
                    auto itr = cm_sessions.begin();
                    for (; itr != cm_sessions.end(); ++itr) {
                        if (!itr->second->IsPinned()) {
                            if (itr->second->IsExpired()) {
                                break;
                            }
                        }
                    }
                    if (itr != cm_sessions.end()) {
                        cm_sessions.erase(itr);
                    } else {
                        break;
                    }
                }
            } catch (...) {
            }
        }
        if (cm_started) {
            const boost::chrono::nanoseconds ns(static_cast<uint64_t>(MAX_SESSION_MANAGER_THREAD_SLEEP_IN_SEC) * 1000 * 1000 * 1000);
            boost::this_thread::sleep_for(ns);
        }
    }
}

void AppSessionManager::StopCleanUpThread()
{
    cm_started = false;
    cm_thread.join();
}

}