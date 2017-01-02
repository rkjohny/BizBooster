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

#include "LoggedInHelper.h"
#include "AppSessionManager.h"

namespace Api {

void LoggedInHelper::InitAndValidate()
{
    auto dao = Dal::GetDao();
    m_user = dao->GetUser(m_requester, m_input->GetUserId());
    if (!m_user) {
        throw Common::AppException(AppErrorCode::USER_NOT_FOUND, "User not exists");
    }
}

void LoggedInHelper::CheckPermission()
{
}

void LoggedInHelper::ExecuteHelper()
{
    Api::AppSessionManager::AddSession(m_input->GetSessionToken(), m_user, m_input->GetSessionExpires());
    m_output->SetUser(*m_user);
}


}