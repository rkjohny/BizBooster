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


#include "AppDef.h"
#include <memory>

namespace Api {

//TODO: Use Forward declaration class BaseInput and BaseOutput if needed.

template<class InputT, class OutputT>
class AbstractHelper {
private:
    NON_COPY_NON_MOVE_ABLE(AbstractHelper);

protected:
    std::shared_ptr<InputT> m_input;
    std::shared_ptr<OutputT> m_output;

public:

    AbstractHelper(std::shared_ptr<InputT> input, std::shared_ptr<OutputT> output = nullptr) :
    m_input(input), m_output(output)
    {
        if (!m_output) {
            m_output = std::make_shared<OutputT>();
        }
    }

    virtual ~AbstractHelper() = default;

    virtual void InitAndValidate() = 0;

    virtual void CheckPermission() = 0;

    virtual void ExecuteHelper() = 0;

    std::shared_ptr<OutputT> GetOutput()
    {
        return m_output;
    }

    std::shared_ptr<InputT> Getinput()
    {
        return m_input;
    }

    web::json::value Execute();
};

} /* namespace Api */

#endif /* ABSTRACT_HELPER_H */
