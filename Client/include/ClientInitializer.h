#ifndef _CLIENT_APP_INITIALIZER_H_
#define _CLIENT_APP_INITIALIZER_H_


namespace Client
{

class ClientInitializer
{
private:
    ClientInitializer();
    ClientInitializer( ClientInitializer& );
    ClientInitializer& operator = ( ClientInitializer& );

public:
    static void Initialize();
};

}
#endif
