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
    try {
        Wt::Dbo::Transaction transaction = Dal::GetDao()->BeginTransaction();

        ValidateInput();
        Initialize();
        CheckPermission();
        ExecuteHelper();

        response = m_output->Serialize();
        bool succeeded = transaction.commit();

    } catch (AppException& e) {
        //         LOG_ERROR(std::string("API: ") + m_input->ApiName() +
        //                    " failed with with error: [" + e.ToString() + "]" );
    } catch (exception& e) {
        //         LOG_ERROR(std::string("API: ") + m_input->ApiName() + " failed with with error: [" +
        //                    AppException( e ).ToString() + "]" );
    }

    // the output must be deleted by caller
    //return m_output;
    return response;
}

} /* namespace Api */
