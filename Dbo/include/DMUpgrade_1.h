#ifndef _DMUPGRADE_1_H
#define _DMUPGRADE_1_H


#include "DMUpgrade.h"

namespace Dal {

class DMUpgrade_1 : public DMUpgrade {
public:
    constexpr DMUpgrade_1() = default;

    void Execute() override;
};

}


#endif //BIZBOOSTER_DMUPGRADE_1_H
