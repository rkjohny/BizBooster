
#ifndef _APP_SETTIGNS_H_
#define _APP_SETTIGNS_H_

#include <string>
#include <Wt/Dbo/Dbo>
#include "SerializableEntity.h"



namespace Dal {

class AppSetting : public SerializableEntity<AppSetting> {
private:
    std::string m_name;
    std::string m_value;

public:
    AppSetting() = default;

    AppSetting(const std::string &&name);

    AppSetting(const std::string &&name, const std::string &&value);

    const std::string &GetName() const;

    void SetName(std::string name);

    const std::string &GetValue() const;

    void SetValue(std::string value);


    template<class Action>
    void persist(Action &a)
    {
        Wt::Dbo::id(a, m_name, "name");
        Wt::Dbo::field(a, m_value, "value");
    }

    REGISTER_GETTER_INCLUDING_BASE_START(SerializableEntity < AppSetting >)
    GETTER(AppSetting, const std::string&, "name", &AppSetting::GetName),
    GETTER(AppSetting, const std::string&, "value", &AppSetting::GetValue)
    REGISTER_GETTER_INCLUDING_BASE_END

    REGISTER_SETTER_INCLUDING_BASE_START(SerializableEntity < AppSetting >)
    SETTER(AppSetting, std::string, "name", &AppSetting::SetName),
    SETTER(AppSetting, std::string, "value", &AppSetting::SetValue)
    REGISTER_SETTER_INCLUDING_BASE_END
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

#endif //_APP_SETTIGNS_H_
