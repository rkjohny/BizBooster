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

#include "SaveUserOutput.h"

namespace Mocxygen {


    void SaveUserOutput::CopyFrom(const SaveUserOutput &&orig) {
        if (orig.m_entity) {
            m_entity = std::move(orig.m_entity);
        }
    }

    void SaveUserOutput::CopyFrom(const SaveUserOutput &orig) {
        if (orig.m_entity) {
            m_entity = orig.m_entity;
        }
    }


    std::string SaveUserOutput::Name() const {
        return "SaveUserOutput";
    }

    std::string SaveUserOutput::ToString() const {
        return "SaveUserOutput";
    }

} /* namespace Mocxygen */
