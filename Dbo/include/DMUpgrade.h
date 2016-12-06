#ifndef _DM_UPGRADE_H
#define _DM_UPGRADE_H


namespace Dal {

class DMUpgrade {
public:
    constexpr DMUpgrade() = default;
    virtual ~DMUpgrade() = default;

    virtual void Execute() = 0;
};

}


#endif