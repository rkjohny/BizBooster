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


#ifndef THREAD_H
#define THREAD_H

#include "AppCommonDef.h"
#include <mutex>
#include <pthread.h>

namespace Common {

#if 0

template <class T, class ArgT>
class Thread {
private:
    NON_COPY_NON_MOVE_ABLE(Thread);

    typedef void (T::*ThreadFunc)(ArgT);

    void *ThFun(void *arg)
    {
        (*(m_obj->m_fp))(dynamic_cast<ArgT*> (arg));

        return nullptr;
    }

    pthread_t m_th;
    volatile bool m_started;
    ThreadFunc m_fp;
    T *m_obj;

public:

    Thread(T *obj, ThreadFunc fp) : m_obj(obj), m_fp(fp), m_started(false)
    {
    }

    virtual ~Thread()
    {
    }

    void Start(ArgT *arg)
    {
        if (!m_started) {
            pthread_create(&m_th, nullptr, ThFun, (void*) arg);
        }
    }


};
#endif

template <class T>
class Thread {
private:
    NON_COPY_NON_MOVE_ABLE(Thread);

    typedef void (T::*ThreadFunc)(void);

    static void *RunThread(void *arg)
    {
        Thread *thObj = static_cast<Thread*> (arg);

        (thObj->m_obj->*(thObj->m_fp))();

        return nullptr;
    }

    T *m_obj;
    pthread_t m_th;
    volatile bool m_started;
    ThreadFunc m_fp;

public:

    Thread(T *obj, ThreadFunc fp) : m_obj(obj), m_started(false), m_fp(fp)
    {
    }

    virtual ~Thread()
    {
    }

    bool Start()
    {
        if (!m_started) {
            int res = pthread_create(&m_th, nullptr, RunThread, static_cast<void *> (this));
            m_started = res == 0;
        }
        return m_started;
    }

    bool IsRunning()
    {
        return m_started;
    }
    
    void Join()
    {
        m_started = false;
        pthread_join(m_th, nullptr);
    }
};

template<>
class Thread<void> {
private:
    NON_COPY_NON_MOVE_ABLE(Thread);

    typedef void (*ThreadFunc)(void);

    static void *RunThread(void *arg)
    {
        Thread *thObj = static_cast<Thread*> (arg);

        (*(thObj->m_fp))();

        return nullptr;
    }

    pthread_t m_th;
    volatile bool m_started;
    ThreadFunc m_fp;

public:

    Thread(ThreadFunc fp) : m_started(false), m_fp(fp)
    {
    }

    virtual ~Thread()
    {
    }

    bool Start()
    {
        if (!m_started) {
            int res = pthread_create(&m_th, nullptr, RunThread, static_cast<void *> (this));
            m_started = res == 0;
        }
        return m_started;
    }

    bool IsRunning()
    {
        return m_started;
    }
    
    void Join()
    {
        m_started = false;
        pthread_join(m_th, nullptr);
    }
};

}

#endif /* THREAD_H */

