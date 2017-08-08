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


#ifndef SINGLE_TON_H
#define SINGLE_TON_H

#include "Disposable.h"
#include "boost/thread.hpp"

namespace Common {


template<class T>
class SingleTon {
protected:
    static T *m_instance;
    
    SingleTon() = default;
    virtual ~SingleTon() = default;
    
    static boost::once_flag m_onceFlag;
    
    static void Init() noexcept {
        // no need to use mutex
        if (!m_instance) {
            m_instance = new T();
        }
    }
    
public:
    static T* GetInstance() {
        boost::call_once(Init, m_onceFlag);
        return m_instance;
    }    
};

template<class T>
T* SingleTon<T>::m_instance = nullptr;

template<class T>
boost::once_flag SingleTon<T>::m_onceFlag = BOOST_ONCE_INIT;

}
#endif /* SINGLE_TON_H */

