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

#include <mutex>
#include "Disposable.h"

namespace Common {


template<class T>
class SingleTon {
protected:
    static T *m_instance;
    
    SingleTon() = default;
    virtual ~SingleTon() = default;
    
    static std::mutex m_mutex;
    
public:
    static T* GetInstance() {
        m_mutex.lock();
        if (!m_instance) {
            m_instance = new T();
        }
        m_mutex.unlock();
        return m_instance;
    }    
};

template<class T>
T* SingleTon<T>::m_instance = nullptr;

template<class T>
std::mutex SingleTon<T>::m_mutex;

}
#endif /* SINGLE_TON_H */

