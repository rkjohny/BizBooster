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

#ifndef LOGFIG_OUTPUT_STREAM_H
#define LOGFIG_OUTPUT_STREAM_H

#include <mutex>
#include <string>
#include "AppCommonDef.h"

namespace Logfig {
    using namespace std;

    class OStream {
    private:
        NON_COPY_NON_MOVE_ABLE(OStream);
        
    protected:
        bool m_is_open;
        mutex m_mutex;

    public:
        OStream();
        virtual ~OStream();

        virtual void Open() = 0;
        virtual void Flush() = 0;

        virtual void Write(const string&& message) = 0;
        virtual void Write(const string& message) = 0;
        virtual void Close() = 0;
    };

} /* namespace Logfig */

#endif /* LOGFIG_OUTPUT_STREAM_H */
