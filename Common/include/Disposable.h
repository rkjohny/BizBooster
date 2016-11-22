/*
 * Disposable.h
 *
 *  Created on: Oct 11, 2016
 *      Author: rezaul
 */

#ifndef DISPOSABLE_H_
#define DISPOSABLE_H_

namespace Common {

class Disposable
{
protected:
    bool m_isDosposed;

public:
    Disposable();
    virtual ~Disposable();
    virtual void Dispose() = 0;
};

} /* namespace Common */

#endif /* DISPOSABLE_H_ */
