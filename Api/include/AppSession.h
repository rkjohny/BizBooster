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

#ifndef APP_SESSION_H
#define APP_SESSION_H

#include <ctime>
#include <memory>
#include "User.h"
#include "AuthenticatedRequester.h"



namespace Api {

class AppSession {
    friend class AppSessionManager;

protected:
    AppSession();

public:
    bool IsExpired();
    virtual~AppSession();

    std::weak_ptr<Dal::AuthenticatedRequester> GetRequester();

    void SetUser(const Dal::User &user);

    void ExtendExpiration();

    void ResetExpiration(uint64_t msec);

    void ExtendExpiration(uint64_t msec);

    const Dal::User& Getuser();

    bool IsPinned() const;

    void SetPinned(volatile bool pinned);

private:
    std::shared_ptr<Dal::AuthenticatedRequester> m_requester;
    time_t m_tmExpiresOn;

    volatile bool m_pinned;
};

}
#endif /* APP_SESSION_H */

