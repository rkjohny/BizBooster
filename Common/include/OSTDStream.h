/*
 * OSTDStream.h
 *
 *  Created on: Oct 12, 2016
 *      Author: rezaul
 */

#ifndef OSTDSTREAM_H_
#define OSTDSTREAM_H_

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
