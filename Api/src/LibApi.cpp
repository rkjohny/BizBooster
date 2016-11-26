/*
 * TradeXApiLibrary.cpp
 *
 *  Created on: Oct 14, 2016
 *      Author: rezaul
 */

#include "LibApi.h"

#include "Json.h"
#include "RegisterUserInput.h"

namespace Api
{

void LoadLibrary()
{
    RegisterUserInput ruin;
    Json::LoadLibrary();
}


} /* namespace  */
