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

#include "BaseInput.h"
#include "BaseOutput.h"
#include "AppDef.h"
#include <memory>

namespace Api {

    //TODO: Use Forward declaration class BaseInput and BaseOutput if needed.

    class AbstractHelper {
    private:
        NON_COPY_NON_MOVE_ABLE(AbstractHelper);

    protected:
        std::unique_ptr<BaseOutput> m_output;
        BaseInput *m_input;

    public:
        AbstractHelper();
        virtual ~AbstractHelper();

        virtual void InitAndValidate() = 0;

        virtual void CheckPermission() = 0;

        virtual void ExecuteHelper() = 0;

        web::json::value Execute();
    };

} /* namespace Api */

#endif /* ABSTRACT_HELPER_H */
