/**
 * AbstractHelper.cpp
 *
 *      Author: rezaul
 *
 * Copyright (C) 2016 Rezaul Karim, rkjohny@gmail.com. All rights reserved.
 */

#include "RegisterUserOutput.h"
#include "Converter.h"
#include "AbstractHelper.h"
#include "Dao.h"
#include "Dal.h"
#include "AppException.h"
#include "AppFactory.h"
#include "ApiUtils.h"

namespace Api {
using namespace Common;

AbstractHelper::AbstractHelper() : m_output(nullptr)
{
}

AbstractHelper::~AbstractHelper()
{
}

web::json::value AbstractHelper::Execute()
{
    web::json::value response;
    auto dao = Dal::GetDao();
    auto transaction = dao->BeginTransaction();
    try {
        ValidateInput();
        Initialize();
        CheckPermission();
        ExecuteHelper();

        response = m_output->Serialize();
        //TODO: what to do  if commit failes
        bool succeeded = dao->CommitTransaction(transaction);

    } catch (AppException &e) {
        dao->RollbackTransaction(transaction);
        response = ApiUtils::ErrorResponse(e.GetCode(), e.GetMessage());
        LOG_ERROR(std::string("Input: ") + m_input->ToString() +
                            " failed with with error: [" + e.ToString() + "]" );
    } catch (exception &e) {
        dao->RollbackTransaction(transaction);
        AppException ex = AppException( e );
        response = ApiUtils::ErrorResponse(ex.GetCode(), ex.GetMessage());
        LOG_ERROR(std::string("API: ") + m_input->ToString() +
                          " failed with with error: [" +  ex.ToString() + "]" );
    }

    return response;
}

} /* namespace Api */
