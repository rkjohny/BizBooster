//
// Created by rezaul on 12/4/16.
//

#ifndef BIZBOOSTER_DBO_H
#define BIZBOOSTER_DBO_H

#include "Dao.h"
#include <memory>

namespace Dal {

    void LoadLibrary();

    std::shared_ptr<Dao> GetDao();
};


#endif //BIZBOOSTER_DBO_H
