
#include "AppSetting.h"

namespace Dal {

AppSetting::AppSetting(const std::string &&name) : m_name{ std::move(name) }
{}

AppSetting::AppSetting(const std::string &&name, const std::string &&value) :
        m_name{ std::move(name) }, m_value{ std::move(value) }
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
