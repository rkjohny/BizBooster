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

void OSTDStream::Write(const string&& message)
{
    m_mutex.lock();
    cout << message << endl;
    m_mutex.unlock();
}

void OSTDStream::Close()
{
}

} /* namespace Common */
