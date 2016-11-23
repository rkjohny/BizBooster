#include "ServerDisposer.h"
#include "AppFactory.h"

using namespace Common;
using namespace Server;

void ServerDisposer::Dispose()
{
    AppFactory::Dispose();
}
