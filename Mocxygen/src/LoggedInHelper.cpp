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

#include "LoggedInHelper.h"
#include "AppSessionManager.h"

namespace Mocxygen {


void LoggedInHelper::ExecuteHelper() noexcept(false)
{
    auto userService = Cruxdb::GetUserService();
    if (m_input->GetId() && m_input->GetSessionToken() && m_input->GetSessionExpiresInMS()) {
        m_user = userService->GetUser(m_requester, *m_input->GetId());
        if (!m_user) {
            throw Common::AppException(AppErrorCode::USER_NOT_FOUND, "User not exists");
        }

        Mocxygen::AppSessionManager::AddSession(*m_input->GetSessionToken(), m_user, *m_input->GetSessionExpiresInMS());
        m_output->SetEntity(m_user);
    }
}


}