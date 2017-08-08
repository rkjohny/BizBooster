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

#include "OFStream.h"

namespace Logfig {

OFStream::OFStream() :
OStream()
{
}

OFStream::OFStream(const std::string &filename) : m_ofs(filename, std::ios_base::app)
{
    m_is_open = m_ofs.is_open();
}

OFStream::~OFStream()
{
    OFStream::Close();
}

void OFStream::SetFile(const std::string &filename)
{
    boost::lock_guard<boost::mutex> guard(m_mutex);
    try {
        if (m_is_open) {
            m_is_open = false;
            m_ofs.flush();
            m_ofs.close();
        }
        this->m_fileName = filename;
        m_ofs.open(m_fileName, std::ios_base::out | std::ios_base::app);
        m_is_open = m_ofs.is_open();
    } catch (...) {
    }
}

void OFStream::Open()
{
    boost::lock_guard<boost::mutex> guard(m_mutex);
    if (!m_is_open) {
        try {
            m_ofs.open(m_fileName, std::ios_base::app);
            m_is_open = m_ofs.is_open();
        } catch (...) {
        }
    }
}

void OFStream::Flush()
{
    boost::lock_guard<boost::mutex> guard(m_mutex);
    if (m_is_open) {
        try {
            m_ofs.flush();
        } catch (...) {
        }
    }
}

void OFStream::Write(const std::string&& message)
{
    boost::lock_guard<boost::mutex> guard(m_mutex);
    if (m_is_open) {
        try {
            // endl will flush stream
            m_ofs << std::move(message) << std::endl;
            //m_ofs.flush();
        } catch (...) {
        }
    }
}

void OFStream::Write(const std::string& message)
{
    boost::lock_guard<boost::mutex> guard(m_mutex);
    if (m_is_open) {
        try {
            // endl will flush stream
            m_ofs << message << std::endl;
            //m_ofs.flush();
        } catch (...) {
        }
    }
}

void OFStream::Close()
{
    boost::lock_guard<boost::mutex> guard(m_mutex);
    if (m_is_open) {
        try {
            m_is_open = false;
            m_ofs.flush();
            m_ofs.close();
        } catch (...) {
        }
    }
}
} /* namespace Common */
