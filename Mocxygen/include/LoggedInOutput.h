/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   LoggedInOutput.h
 * Author: Rezaul Karim
 * Email:  rezaul@gmail.com
 *
 * Created on January 1, 2017, 5:29 PM
 */

#ifndef LOGGED_IN_OUTPUT_H
#define LOGGED_IN_OUTPUT_H

#include "BaseOutput.h"
#include "AppCommonDef.h"
#include "User.h"

namespace Mocxygen {

class LoggedInOutput : public Mocxygen::ApiOutput<LoggedInOutput> {
public:
    API_OUTPUT(LoggedInOutput);

    virtual ~LoggedInOutput();

    const Cruxdb::User& GetUser() const;

    void SetUser(const Cruxdb::User &user);

    REGISTER_GETTER_INCLUDING_BASE_START(ApiOutput<LoggedInOutput>)
    GETTER(LoggedInOutput, const Cruxdb::User&, "user_id", &LoggedInOutput::GetUser)
    REGISTER_GETTER_INCLUDING_BASE_END

    REGISTER_SETTER_INCLUDING_BASE_START(ApiOutput<LoggedInOutput>)
    SETTER(LoggedInOutput, const Cruxdb::User&, "user_id", &LoggedInOutput::SetUser)
    REGISTER_SETTER_INCLUDING_BASE_END

private:
    Cruxdb::User m_user;
};

}

#endif /* LOGGEDIN_OUTPUT_H */
