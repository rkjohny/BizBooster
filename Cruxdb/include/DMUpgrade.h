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

#ifndef DM_UPGRADE_H
#define DM_UPGRADE_H


namespace Cruxdb {

class DMUpgrade {
public:
    constexpr DMUpgrade() = default;
    virtual ~DMUpgrade() = default;

    virtual void Execute() = 0;
};

}


#endif //DM_UPGRADE_H