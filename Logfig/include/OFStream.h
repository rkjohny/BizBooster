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

#ifndef LOGFIG_OUTPUT_FILE_STREAM_H
#define LOGFIG_OUTPUT_FILE_STREAM_H

#include <fstream>
#include <string>

#include "AppCommonDef.h"
#include "OStream.h"

namespace Logfig {
    using namespace std;

    class OFStream : public OStream {
    private:
        NON_COPY_NON_MOVE_ABLE(OFStream);
        
        ofstream m_ofs;
        string m_fileName;
            
    public:
        OFStream();
        explicit OFStream(const string &filename);
        virtual ~OFStream();

        void SetFile(const string &filename);

        void Open() override;
        void Flush() override;
        void Write(const string&& message) override;
        void Write(const string& message) override;
        void Close() override;
    };

} /* namespace Logfig */

#endif /* LOGFIG_OUTPUT_FILE_STREAM_H */
