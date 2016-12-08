/*
 * OStream.h
 *
 *  Created on: Oct 11, 2016
 *      Author: rezaul
 */

#ifndef OSTREAM_H_
#define OSTREAM_H_

#include <mutex>
#include <string>

namespace Common {
    using namespace std;

    class OStream {
    protected:
        bool m_is_open;
        mutex m_mutex;

    public:
        OStream();
        virtual ~OStream();

        virtual void Open() = 0;
        virtual void Flush() = 0;

        virtual void Write(const string&& message) = 0;
        virtual void Close() = 0;
    };

} /* namespace Common */

#endif /* OSTREAM_H_ */
