/*
 * OFStream.h
 *
 *  Created on: Oct 11, 2016
 *      Author: rezaul
 */

#ifndef OFSTREAM_H_
#define OFSTREAM_H_

#include <fstream>
#include <string>
#include "OStream.h"

namespace Common {
    using namespace std;

    class OFStream : public OStream {
    private:
        ofstream m_ofs;
        string m_fileName;

    public:
        OFStream();
        explicit OFStream(const string& filename);
        virtual ~OFStream();

        void SetFile(const string& filename);

        void Open() override;
        void Flush() override;
        void Write(const string& message) override;
        void Close() override;
    };

} /* namespace Common */

#endif /* OFSTREAM_H_ */
