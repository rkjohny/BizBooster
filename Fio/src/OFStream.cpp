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

#include "OFStream.h"

namespace Fio {

OFStream::OFStream() :
OStream()
{
}

OFStream::OFStream(const string &filename) : m_ofs(filename, ios_base::app)
{
    m_is_open = m_ofs.is_open();
}

OFStream::~OFStream()
{
    OFStream::Close();
}

void OFStream::SetFile(const string &filename)
{
    m_mutex.lock();
    try {
        if (m_is_open) {
            m_is_open = false;
            m_ofs.flush();
            m_ofs.close();
        }
        this->m_fileName = filename;
        m_ofs.open(m_fileName, ios_base::out | ios_base::app);
        m_is_open = m_ofs.is_open();
    } catch (...) {
    }
    m_mutex.unlock();
}

void OFStream::Open()
{
    m_mutex.lock();
    if (!m_is_open) {
        try {
            m_ofs.open(m_fileName, ios_base::app);
            m_is_open = m_ofs.is_open();
        } catch (...) {
        }
    }
    m_mutex.unlock();
}

void OFStream::Flush()
{
    m_mutex.lock();
    if (m_is_open) {
        try {
            m_ofs.flush();
        } catch (...) {
        }
    }
    m_mutex.unlock();
}

void OFStream::Write(const string&& message)
{
    m_mutex.lock();
    if (m_is_open) {
        try {
            // endl will flush stream
            m_ofs << std::move(message) << endl;
            //m_ofs.flush();
        } catch (...) {
        }
    }
    m_mutex.unlock();
}

void OFStream::Write(const string& message)
{
    m_mutex.lock();
    if (m_is_open) {
        try {
            // endl will flush stream
            m_ofs << message << endl;
            //m_ofs.flush();
        } catch (...) {
        }
    }
    m_mutex.unlock();
}

void OFStream::Close()
{
    m_mutex.lock();
    if (m_is_open) {
        try {
            m_is_open = false;
            m_ofs.flush();
            m_ofs.close();
        } catch (...) {
        }
    }
    m_mutex.unlock();
}
} /* namespace Common */
