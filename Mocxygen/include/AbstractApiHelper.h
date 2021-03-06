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
    std::shared_ptr<InputT> m_input;
    std::shared_ptr<OutputT> m_output;

    std::shared_ptr<Cruxdb::Requester> m_requester;

public:

    AbstractApiHelper(std::shared_ptr<Cruxdb::Requester> requester, std::shared_ptr<InputT> input,
                      std::shared_ptr<OutputT> output = nullptr) :
    m_input(input), m_requester(requester)
    {
        if (!output) {
            m_output = std::make_shared<OutputT>();
        } else {
            m_output = output;
        }
    }

    virtual ~AbstractApiHelper() = default;

    virtual void ExecuteHelper() = 0;

    std::shared_ptr<OutputT> GetOutput()
    {
        return m_output;
    }

    virtual std::shared_ptr<InputT> GetInput()
    {
        return m_input;
    }

    std::shared_ptr<AbstractBaseOutput> Execute() override
    {
        web::json::value response;
        auto dao = Cruxdb::GetUserService();
        Wt::Dbo::Transaction && transaction =  Wt::Dbo::Transaction(*dao->GetSession());
        try {

            ExecuteHelper();
            
            if (m_output->GetError().GetCode() == AppErrorCode::SUCCESS) {
                m_output->Serialize();
                //TODO: what to do  if commit failes
                bool succeeded = transaction.commit(); // dao->CommitTransaction(m_requester, std::move(transaction));                
            } else {
                transaction.rollback();
                response = m_output->GetErrorResponse();
                LOG_ERROR(std::string("Input: ") + m_input->Name() +
                        " failed with with error: [" + response.serialize() + "]");
            }
        } catch (Common::AppException &e) {
            transaction.rollback();            
            m_output->SetError(ApiError(e.GetCode(), e.GetMessage()));
            
            response = e.Serialize();
            LOG_ERROR(std::string("Input: ") + m_input->Name() +
                    " failed with with error: [" + response.serialize() + "]");
        } catch (std::exception &e) {
            transaction.rollback();
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
