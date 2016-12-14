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

#ifndef SERVER_DISPOSER_H
#define SERVER_DISPOSER_H


namespace Rest {

    class ServiceDisposer {
    private:
        ServiceDisposer();
        ServiceDisposer(const ServiceDisposer&);
        ServiceDisposer& operator=(ServiceDisposer&);

    public:
        static void Dispose();
    };


} //namespace Server

#endif
