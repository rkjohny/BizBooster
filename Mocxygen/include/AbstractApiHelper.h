/**
 * AbstractHelper.h
 *
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
#ifndef ABSTRACT_HELPER_H
#define ABSTRACT_HELPER_H


#include "AbstractBaseHelper.h"
#include "AppCommonDef.h"
#include "LibCruxdb.h"
#include "AppException.h"
#include "LoggerFactory.h"
#include <cpprest/json.h>
#include <memory>


namespace Mocxygen {


template<class InputT, class OutputT>
class AbstractApiHelper : public AbstractBaseHelper {
private:
    NON_COPY_NON_MOVE_ABLE(AbstractApiHelper);

protected:
    InputT *m_input;
    std::shared_ptr<OutputT> m_output;

    Cruxdb::Requester *m_requester;

public:

    AbstractApiHelper(Cruxdb::Requester * requester, InputT *input, OutputT *output = nullptr) :
    m_input(input), m_output(nullptr), m_requester(requester)
    {
        if (!output) {
            m_output = std::make_shared<OutputT>();
        } else {
            m_output = std::shared_ptr<OutputT>(output);
        }
    }

    virtual ~AbstractApiHelper() = default;

    virtual void ExecuteHelper() = 0;

    std::shared_ptr<OutputT> GetOutput()
    {
        return m_output;
    }

    virtual InputT* GetInput()
    {
        return m_input;
    }

    std::shared_ptr<AbstractBaseOutput> Execute() override
    {
        web::json::value response;
        auto dao = Cruxdb::GetUserService();
        auto transaction = dao->BeginTransaction(m_requester);
        try {

            ExecuteHelper();
            
            if (m_output->GetError().GetCode() == AppErrorCode::SUCCESS) {
                m_output->Serialize();
                //TODO: what to do  if commit failes
                bool succeeded = dao->CommitTransaction(m_requester, transaction);                
            } else {
                dao->RollbackTransaction(m_requester, transaction);
                response = m_output->GetErrorResponse();
                LOG_ERROR(std::string("Input: ") + m_input->Name() +
                        " failed with with error: [" + response.serialize() + "]");
            }
        } catch (Common::AppException &e) {
            dao->RollbackTransaction(m_requester, transaction);
            
            m_output->SetError(ApiError(e.GetCode(), e.GetMessage()));
            
            response = e.Serialize();
            LOG_ERROR(std::string("Input: ") + m_input->Name() +
                    " failed with with error: [" + response.serialize() + "]");
        } catch (std::exception &e) {
            dao->RollbackTransaction(m_requester, transaction);
            Common::AppException ex = Common::AppException(e);
            
            m_output->SetError(ApiError(ex.GetCode(), ex.GetMessage()));
            
            response = ex.Serialize();
            LOG_ERROR(std::string("Input: ") + m_input->Name() +
                    " failed with with error: [" + response.serialize() + "]");
        }

        return m_output;
    }
};

} /* namespace Mocxygen */

#endif /* ABSTRACT_HELPER_H */
