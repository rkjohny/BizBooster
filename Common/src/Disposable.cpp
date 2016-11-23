/*
 * Disposable.cpp
 *
 *  Created on: Oct 11, 2016
 *      Author: rezaul
 */

#include "Disposable.h"

namespace Common
{

Disposable::Disposable() :
    m_isDosposed( false )
{
}

Disposable::~Disposable()
{
}

} /* namespace Common */
