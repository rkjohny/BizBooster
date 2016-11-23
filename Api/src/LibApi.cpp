/*
 * TradeXApiLibrary.cpp
 *
 *  Created on: Oct 14, 2016
 *      Author: rezaul
 */

#include "LibApi.h"

#include "RegisterUserInput.h"

namespace Api
{

void LibApi::LoadLibrary()
{
    Api::RegisterUserInput().RegisterClass();
    Api::User().RegisterClass();
}

} /* namespace TeamBoosterCommon */
