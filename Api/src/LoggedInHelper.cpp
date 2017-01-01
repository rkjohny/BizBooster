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
#include "SessionManager.h"

namespace Api {

void LoggedInHelper::InitAndValidate()
{
    m_dao = Dal::GetDao();
    m_user = m_dao->GetUser(m_requester, m_input->GetUserId());
    if (!m_user) {
        throw Common::AppException(AppErrorCode::USER_NOT_FOUND, "User not exists");
    }
}

void LoggedInHelper::CheckPermission()
{

}

void LoggedInHelper::ExecuteHelper()
{
    //Dal::SessionManager::AddSession(m_input->GetSessionToken(), *m_user, m_input->GetSessionExpires());
}


}