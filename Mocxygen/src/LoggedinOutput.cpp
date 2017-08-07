/**
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


#include "LoggedinOutput.h"


namespace Mocxygen {

    LoggedinOutput::~LoggedinOutput() {
    }

    void LoggedinOutput::CopyFrom(const LoggedinOutput &&orig) {
        if (orig.m_entity) {
            m_entity = std::move(orig.m_entity);
        }
    }

    void LoggedinOutput::CopyFrom(const LoggedinOutput &orig) {
        if (orig.m_entity) {
            m_entity = Wt::Dbo::ptr<Cruxdb::User>(new Cruxdb::User(*orig.m_entity));
        }
    }

    string LoggedinOutput::Name() const {
        return "LoggedInOutput";
    }

    string LoggedinOutput::ToString() const  {
        return "LoggedInOutput";
    }
}

