#include "ClientDisposer.h"
#include "AppFactory.h"

using namespace Common;
using namespace Client;

void ClientDisposer::Dispose()
{
    AppFactory::Dispose();
}
