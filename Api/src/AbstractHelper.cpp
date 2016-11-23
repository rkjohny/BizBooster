/**
 * AbstractHelper.cpp
 *
 *      Author: rezaul
 *
 * Copyright (C) 2016 Rezaul Karim, rkjohny@gmail.com. All rights reserved.
 */

#include "AbstractHelper.h"
#include "BaseInput.h"
#include "BaseOutput.h"
#include "AppException.h"
#include "AppFactory.h"

namespace Api
{
using namespace Common;

AbstractHelper::AbstractHelper() :
    m_output( nullptr ), m_input( nullptr )
{
}

AbstractHelper::~AbstractHelper()
{
    if ( m_input )
    {
        delete m_input;
    }
}

BaseOutput* AbstractHelper::Execute()
{
    try
    {
        ValidateInput();
        Initialize();
        CheckPermission();
        ExecuteHelper();
    }
    catch ( AppException& e )
    {
        LOG_ERROR( "API: " + m_input->ApiName() +
                   " failed with with error: [" + e.ToString() + "]" );
    }
    catch ( exception& e )
    {
        LOG_ERROR( "API: " + m_input->ApiName() + " failed with with error: [" +
                   AppException( e ).ToString() + "]" );
    }

    // the output must be deleted by caller
    return m_output;
}

} /* namespace Api */
