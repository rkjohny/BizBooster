/**
 * AbstractHelper.h
 *
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
#ifndef ABSTRACT_HELPER_H
#define ABSTRACT_HELPER_H


#include "BaseHelper.h"
#include "AppDef.h"
#include "Dal.h"
#include "AppException.h"
#include "LogFactory.h"
#include <cpprest/json.h>
#include <memory>


namespace Api {

//TODO: Use Forward declaration class BaseInput and BaseOutput if needed.

template<class InputT, class OutputT>
class ApiHelper : public BaseHelper {
private:
    NON_COPY_NON_MOVE_ABLE(ApiHelper);

protected:
    InputT *m_input;
    OutputT *m_output;
    std::shared_ptr<OutputT> m_outputPtr;
    
    Dal::Requester *m_requester;

public:
    ApiHelper(Dal::Requester * requester, InputT *input, OutputT *output = nullptr) :
    m_input(input), m_output(output), m_outputPtr(nullptr)
    {
        if (!m_output) {
            m_outputPtr = std::make_shared<OutputT>();
            m_output = m_outputPtr.get();
            //m_output = new OutputT();
            //m_outputPtr = std::shared_ptr<OutputT>(m_output);
        } else {
        }
        m_requester = requester;
    }

    virtual ~ApiHelper() = default;

    virtual void ExecuteHelper() = 0;
    
    virtual OutputT* GetOutput()
    {
        return m_output;
    }

    virtual InputT* Getinput()
    {
        return m_input;
    }

    web::json::value Execute() override
    {
        web::json::value response;
        auto dao = Dal::GetDao();
        auto transaction = dao->BeginTransaction(m_requester);
        try {
            InitAndValidate();
            CheckPermission();
            
            ExecuteHelper();

            response = m_output->Serialize();

            //TODO: what to do  if commit failes
            bool succeeded = dao->CommitTransaction(m_requester, transaction);

        } catch (Common::AppException &e) {
            dao->RollbackTransaction(m_requester, transaction);
            response = e.Serialize();
            //response = ApiUtils::ErrorResponse(e.GetCode(), e.GetMessage());
            LOG_ERROR(std::string("Input: ") + m_input->Name() +
                    " failed with with error: [" + e.ToString() + "]");
        } catch (std::exception &e) {
            dao->RollbackTransaction(m_requester, transaction);
            Common::AppException ex = Common::AppException(e);
            response = ex.Serialize();
            //response = ApiUtils::ErrorResponse(ex.GetCode(), ex.GetMessage());
            LOG_ERROR(std::string("Input: ") + m_input->Name() +
                    " failed with with error: [" + ex.ToString() + "]");
        }

        return response;
    }
};

} /* namespace Api */

#endif /* ABSTRACT_HELPER_H */
