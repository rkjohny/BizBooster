#include "ServerDisposer.h"
#include "AppFactory.h"


namespace Server {

void ServerDisposer::Dispose()
{
    Common::AppFactory::Dispose();
}

}
