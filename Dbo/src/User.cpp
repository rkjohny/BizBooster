#include "User.h"

namespace Dal {

    const std::string& User::GetEmail() const
    {
        return m_email;
    }

    const std::string& User::GetName() const
    {
        return m_name;
    }

    const std::string& User::GetRoles() const
    {
        return m_roles;
    }

    void User::SetEmail(std::string email)
    {
        m_email = std::move(email);
    }

    void User::SetName(std::string name)
    {
        m_name = std::move(name);
    }

    void User::SetRoles(std::string roles)
    {
        m_roles = std::move(roles);
    }
}