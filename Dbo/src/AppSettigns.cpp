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

#include "AppSetting.h"

namespace Dal {

AppSetting::AppSetting(const std::string &name) : m_name{name}
{
}

AppSetting::AppSetting(const std::string &&name) : m_name{std::move(name)}
{
}

AppSetting::AppSetting(const std::string &&name, const std::string &&value) :
m_name{std::move(name)}, m_value{ std::move(value)}
{
}

const std::string &AppSetting::GetName() const
{
    return m_name;
}

void AppSetting::SetName(std::string name)
{
    m_name = std::move(name);
}

const std::string &AppSetting::GetValue() const
{
    return m_value;
}

void AppSetting::SetValue(std::string value)
{
    m_value = std::move(value);
}

}
