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


#ifndef LOGFIG_OUTPUT_STD_STREAM_H
#define LOGFIG_OUTPUT_STD_STREAM_H

#include <string>
#include "OStream.h"

namespace Logfig {
    using namespace std;

    class OSTDStream : public OStream {
    private:
        NON_COPY_NON_MOVE_ABLE(OSTDStream);
        
    public:
        OSTDStream();
        ~OSTDStream();

        void Open() override;

        void Flush() override;

        void Write(const string&& message) override;
        void Write(const string& message) override;
        
        void Close() override;
    };

} /* namespace Logfig */

#endif /* LOGFIG_OUTPUT_STD_STREAM_H */
