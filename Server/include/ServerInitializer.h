#ifndef _SERVER_APP_INITIALIZER_H_
#define _SERVER_APP_INITIALIZER_H_


namespace Server
{


class ServerInitializer
{
private:
    ServerInitializer();
    ServerInitializer( ServerInitializer& );
    ServerInitializer& operator = ( ServerInitializer& );

public:
    static void Initialize();
};


} //namespace Server
#endif
