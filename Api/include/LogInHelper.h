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


namespace Api {

class LogInHelper : public AbstractHelper {
public:
    LogInHelper();
    virtual ~LogInHelper();
           
    LogInHelper(LogInInput *input);
    LogInHelper(LogInInput &input);

    void SetInput(LogInInput *in);
    void SetInput(LogInInput &in);
        
    void InitAndValidate() override;

    void CheckPermission() override;
    
    void ExecuteHelper() override;

private:
    NON_COPY_NON_MOVE_ABLE(LogInHelper)
};

}

#endif /* LOGIN_HELPER_H */

