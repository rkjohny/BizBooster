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

#include "ConfigReader.h"

namespace Logfig {

ConfigReader::ConfigReader(ConFigFileType type) : m_type(type)
{
};

void ConfigReader::SetType(ConFigFileType type)
{
    m_type = type;
}

ConFigFileType ConfigReader::GetType() const
{
    return m_type;
}

}