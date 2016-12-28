/**
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

#ifndef LOGIN_HELPER_H
#define LOGIN_HELPER_H

#include "AbstractHelper.h"
#include "LogInInput.h"
#include "LogInOutput.h"


namespace Api {

class LogInHelper : public AbstractHelper<LogInInput, LogInOutput> {
private:
    NON_COPY_NON_MOVE_ABLE(LogInHelper);

public:

    LogInHelper(std::shared_ptr<LogInInput> input, std::shared_ptr<LogInOutput> output) :
    AbstractHelper<LogInInput, LogInOutput>(input, output)
    {
    }

    ~LogInHelper() = default;

    void SetInput(LogInInput *in);
    void SetInput(LogInInput &in);

    void InitAndValidate() override;

    void CheckPermission() override;

    void ExecuteHelper() override;
};

}

#endif /* LOGIN_HELPER_H */

