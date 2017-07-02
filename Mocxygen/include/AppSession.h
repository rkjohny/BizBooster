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

#ifndef APP_SESSION_H
#define APP_SESSION_H

#include <ctime>
#include <memory>
#include "User.h"
#include "AuthenticatedRequester.h"



namespace Mocxygen {

class AppSession {
    friend class AppSessionManager;

protected:
    AppSession();

public:
    bool IsExpired();
    virtual~AppSession();

    std::weak_ptr<Cruxdb::AuthenticatedRequester> GetRequester();

    void SetUser(Wt::Dbo::ptr<Cruxdb::User> &user);

    void ExtendExpiration();

    void ResetExpiration(uint64_t msec);

    void ExtendExpiration(uint64_t msec);

    Wt::Dbo::ptr<Cruxdb::User> Getuser();

    bool IsPinned() const;

    void SetPinned(volatile bool pinned);

private:
    std::shared_ptr<Cruxdb::AuthenticatedRequester> m_requester;
    time_t m_tmExpiresOn;

    volatile bool m_pinned;
};

}
#endif /* APP_SESSION_H */

