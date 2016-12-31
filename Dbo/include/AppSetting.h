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

#ifndef APP_SETTING_H
#define APP_SETTING_H

#include <string>
#include <Wt/Dbo/Dbo>
#include "SerializableAuditableEntity.h"



namespace Dal {

class AppSetting : public SerializableAuditableEntity<AppSetting> {
private:
    std::string m_name;
    std::string m_value;

public:
    AppSetting() = default;
    
    AppSetting(const std::string &name);
        
    AppSetting(const std::string &&name);

    AppSetting(const std::string &&name, const std::string &&value);
    
    AppSetting(const std::string &name, const std::string &value);

    const std::string &GetName() const;

    void SetName(const std::string &name);

    const std::string &GetValue() const;

    void SetValue(const std::string &value);


    template<class Action>
    void persist(Action &a)
    {
        Wt::Dbo::id(a, m_name, "name");
        Wt::Dbo::field(a, m_value, "value");
    }

    REGISTER_GETTER_START
    GETTER(AppSetting, const std::string&, "name", &AppSetting::GetName),
    GETTER(AppSetting, const std::string&, "value", &AppSetting::GetValue)
    REGISTER_GETTER_END

    REGISTER_SETTER_START
    SETTER(AppSetting, const std::string&, "name", &AppSetting::SetName),
    SETTER(AppSetting, const std::string&, "value", &AppSetting::SetValue)
    REGISTER_SETTER_END
};

}


namespace Wt {
namespace Dbo {

template<>
struct dbo_traits<Dal::AppSetting> : public dbo_default_traits {
    typedef std::string IdType;

    static IdType invalidId()
    {
        return std::string();
    }

    static const char *surrogateIdField()
    {
        return 0;
    }
};

}
}

#endif //APP_SETTING_H
