/**
 * AbstractHelper.h
 *
 *      Author: rezaul
 *
 * Copyright (C) 2016 Rezaul Karim, rkjohny@gmail.com. All rights reserved.
 */

#ifndef ABSTRACTHELPER_H_
#define ABSTRACTHELPER_H_

namespace Api {

    //TODO: Forward declaration
    class BaseOutput;
    class BaseInput;

    class AbstractHelper {
    private:
        AbstractHelper(const AbstractHelper& helper) = delete;
        AbstractHelper& operator=(const AbstractHelper&) = delete;

    protected:
        BaseOutput* m_output;

    public:
        AbstractHelper();
        virtual ~AbstractHelper();

        virtual void ValidateInput() = 0;

        virtual void Initialize() = 0;

        virtual void CheckPermission() = 0;

        virtual void ExecuteHelper() = 0;

        BaseOutput* Execute();
    };

} /* namespace Api */

#endif /* ABSTRACTHELPER_H_ */
