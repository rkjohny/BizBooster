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


#ifndef OSTD_STREAM_H
#define OSTD_STREAM_H

#include <string>
#include "OStream.h"

namespace Common {
    using namespace std;

    class OSTDStream : public OStream {
    public:
        OSTDStream();
        ~OSTDStream();

        void Open() override;

        void Flush() override;

        void Write(const string&& message) override;

        void Close() override;
    };

} /* namespace Common */

#endif /* OSTDSTREAM_H_ */
