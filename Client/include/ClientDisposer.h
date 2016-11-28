#ifndef _TRADEX_CLIENT_APP_DISPOSER_H_
#define _TRADEX_CLIENT_APP_DISPOSER_H_


namespace Client {

    class ClientDisposer {
    private:
        ClientDisposer();
        ClientDisposer(const ClientDisposer&);
        ClientDisposer& operator=(ClientDisposer&);

    public:
        static void Dispose();
    };


}


#endif
