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

#include "Session.h"
#include "AppDef.h"
#include "Thread.h"
#include <mutex>

namespace Dal {

class SessionManager {
public:
    using Thread = Common::Thread<void>;
    
    static void AddSession(const std::string &token, const Dal::User &user);

    static bool IsValidToken(const std::string &token);
    
    static bool ResetExpiration(const std::string &token, uint64_t msec);
    
    static bool ResetExpiration(const std::string &token);
    
    static bool SetPinned(const std::string &token, volatile bool pinned);
    
    static Requester* GetRequetser(const std::string &token);
    
    static void StartCleanUpThread();
    
    static void StopCleanUpThread();
    
private:
    MAKE_STATIC(SessionManager);
    
    static std::mutex m_mutex;
    static std::map<std::string, Session*> m_sessions;
    
    static volatile bool m_started;
    static SessionManager::Thread m_thread;
    
    static void Cleanup();
    
};


}
#endif /* SESSIONMANAGER_H */

