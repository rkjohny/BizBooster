#ifndef _TRADEX_SERVER_APP_DISPOSER_H_
#define _TRADEX_SERVER_APP_DISPOSER_H_


namespace Server {

    class ServerDisposer {
    private:
        ServerDisposer();
        ServerDisposer(const ServerDisposer&);
        ServerDisposer& operator=(ServerDisposer&);

    public:
        static void Dispose();
    };


} //namespace Server

#endif
