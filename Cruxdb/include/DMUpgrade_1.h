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


#ifndef DMUPGRADE_1_H
#define DMUPGRADE_1_H


#include "DMUpgrade.h"

namespace Cruxdb {

class DMUpgrade_1 : public DMUpgrade {
public:
    constexpr DMUpgrade_1() = default;

    void Execute() noexcept(false) override;
};

}


#endif //DMUPGRADE_1_H
