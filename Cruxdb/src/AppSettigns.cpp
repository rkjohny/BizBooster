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

#include "AppSetting.h"

namespace Cruxdb {

    AppSetting::AppSetting() {

    }

    AppSetting::AppSetting(const std::string &name) : m_name{name} {
    }

    AppSetting::AppSetting(std::string &&name) : m_name{std::move(name)} {
    }

    AppSetting::AppSetting(const std::string &name, const std::string &value) :
            m_name(name), m_value(value) {
    }

    AppSetting::AppSetting(std::string &&name, std::string &&value) :
            m_name{std::move(name)}, m_value{std::move(value)} {
    }

    const std::string &AppSetting::GetName() const {
        return m_name;
    }

    void AppSetting::SetName(const std::string &name) {
        m_name = name;
    }

    const std::string &AppSetting::GetValue() const {
        return m_value;
    }

    void AppSetting::SetValue(const std::string &value) {
        m_value = value;
    }

}
