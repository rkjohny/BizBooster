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

#include "DMUpgrade_1.h"
#include <memory>
#include "Dao.h"
#include "Dal.h"
#include "AppFactory.h"

namespace Dal {

void DMUpgrade_1::Execute()
{
    //std::shared_ptr<Dao> dao = Dal::GetDao();

    //TODO: create super user
    //LOG_DEBUG("Creating tables ...");
    //dao->CreateTables();
}

}