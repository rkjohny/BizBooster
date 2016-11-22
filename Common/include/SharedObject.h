/*
 * SharedObject.h
 *
 *  Created on: Oct 12, 2016
 *      Author: rezaul
 */

#ifndef SHAREDOBJECT_H_
#define SHAREDOBJECT_H_

#include <mutex>

namespace Common {
using namespace std;

class SharedObject
{
protected:
    SharedObject();
    virtual ~SharedObject();

    mutex m_mutex;
};

} /* namespace Common */

#endif /* SHAREDOBJECT_H_ */
