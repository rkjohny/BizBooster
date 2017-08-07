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


//#include "AbstractHelper.h"
//#include "Cruxdb.h"
//#include "AppException.h"
//#include "LoggerFactory.h"
//
//namespace Mocxygen {
//using namespace Common;
//
//template<class InputT, class OutputT>
//web::json::value AbstractHelper<InputT, OutputT>::Execute()
//{
//    web::json::value response;
//    auto dao = Cruxdb::GetUserService();
//    auto transaction = dao->BeginTransaction();
//    try {
//        InitAndValidate();
//        CheckPermission();
//        ExecuteHelper();
//
//        response = m_output->Serialize();
//        
//        //TODO: what to do  if commit failes
//        bool succeeded = dao->CommitTransaction(transaction);
//
//    } catch (AppException &e) {
//        dao->RollbackTransaction(transaction);
//        response = e.Serialize();
//        //response = ApiUtils::ErrorResponse(e.GetCode(), e.GetMessage());
//        LOG_ERROR(std::string("Input: ") + m_input->Name() +
//                            " failed with with error: [" + e.ToString() + "]" );
//    } catch (exception &e) {
//        dao->RollbackTransaction(transaction);
//        AppException ex = AppException( e );
//        response = ex.Serialize();
//        //response = ApiUtils::ErrorResponse(ex.GetCode(), ex.GetMessage());
//        LOG_ERROR(std::string("Input: ") + m_input->Name() +
//                          " failed with with error: [" +  ex.ToString() + "]" );
//    }
//
//    return response;
//}
//
//} /* namespace Mocxygen */