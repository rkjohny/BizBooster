/*
 * OSTDStream.cpp
 *
 *  Created on: Oct 12, 2016
 *      Author: rezaul
 */

#include "OSTDStream.h"
#include <iostream>

namespace Common {

OSTDStream::OSTDStream()
{
}

OSTDStream::~OSTDStream()
{
}

void OSTDStream::Open()
{
}

void OSTDStream::Flush()
{
}

void OSTDStream::Write(const string& message)
{
    m_mutex.lock();
    cout << message << endl;
    m_mutex.unlock();
}

void OSTDStream::Close()
{
}

} /* namespace Common */
