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

#ifndef SESSION_MANAGER_H
#define SESSION_MANAGER_H

#include "AppSession.h"
#include "AppSession.h"
#include <memory>
#include "boost/thread.hpp"

namespace Mocxygen {

class AppSessionManager {
private:
    MAKE_STATIC(AppSessionManager);
    
public:    
    static void AddSession(const std::string &token, Wt::Dbo::ptr<Cruxdb::User> &user);
    
    static void AddSession(const std::string &token, Wt::Dbo::ptr<Cruxdb::User> &user, uint64_t expiresMsc);

    static bool IsValidToken(const std::string &token);
    
    static bool ResetExpiration(const std::string &token, uint64_t msec);
    
    static bool ResetExpiration(const std::string &token);
    
    static bool SetPinned(const std::string &token, volatile bool pinned);
    
    static std::weak_ptr<AppSession> GetSession(const std::string &token);
    
    static std::weak_ptr<Cruxdb::AuthenticatedRequester> GetRequetser(const std::string &token);
        
    static void StopCleanUpThread();
    
private:
    static std::map<std::string, std::shared_ptr<AppSession>> cm_sessions;
    static boost::mutex cm_mutex;    
    static boost::atomic<bool> cm_started;
    static boost::thread cm_thread;
    
    static void Cleanup();
    
};


}
#endif /* SESSIONMANAGER_H */

