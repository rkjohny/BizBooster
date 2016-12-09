/**
 * AbstractHelper.h
 *
 *      Author: rezaul
 *
 * Copyright (C) 2016 Rezaul Karim, rkjohny@gmail.com. All rights reserved.
 */

#ifndef _ABSTRACT_HELPER_H_
#define _ABSTRACT_HELPER_H_
#include "BaseInput.h"
#include "BaseOutput.h"
#include "AppConfig.h"
#include <memory>

namespace Api {

    //TODO: Use Forward declaration class BaseInput and BaseOutput if needed.

    class AbstractHelper {
    private:
        NON_COPY_NON_ASSIGN_ABLE(AbstractHelper);

    protected:
        std::unique_ptr<BaseOutput> m_output;

    public:
        AbstractHelper();
        virtual ~AbstractHelper();

        virtual void ValidateInput() = 0;

        virtual void Initialize() = 0;

        virtual void CheckPermission() = 0;

        virtual void ExecuteHelper() = 0;

        web::json::value Execute();
    };

} /* namespace Api */

#endif /* ABSTRACTHELPER_H_ */
