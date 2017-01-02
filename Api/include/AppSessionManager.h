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

#ifndef SESSION_MANAGER_H
#define SESSION_MANAGER_H

#include "AppSession.h"
#include "Thread.h"
#include "AppSession.h"
#include <mutex>
#include <memory>

namespace Api {

class AppSessionManager {
public:
    using Thread = Common::Thread<void>;
    
    static void AddSession(const std::string &token, Wt::Dbo::ptr<Dal::User> &user);
    
    static void AddSession(const std::string &token, Wt::Dbo::ptr<Dal::User> &user, uint64_t expiresMsc);

    static bool IsValidToken(const std::string &token);
    
    static bool ResetExpiration(const std::string &token, uint64_t msec);
    
    static bool ResetExpiration(const std::string &token);
    
    static bool SetPinned(const std::string &token, volatile bool pinned);
    
    static std::weak_ptr<AppSession> GetSession(const std::string &token);
    
    static std::weak_ptr<Dal::AuthenticatedRequester> GetRequetser(const std::string &token);
    
    static void StartCleanUpThread();
    
    static void StopCleanUpThread();
    
private:
    MAKE_STATIC(AppSessionManager);
    
    static std::mutex m_mutex;
    static std::map<std::string, std::shared_ptr<AppSession>> m_sessions;
    
    static volatile bool m_started;
    static AppSessionManager::Thread m_thread;
    
    static void Cleanup();
    
};


}
#endif /* SESSIONMANAGER_H */

