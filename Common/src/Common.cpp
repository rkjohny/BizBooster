
#include "Common.h"

namespace Common {

static bool loaded = false;

void LoadLibrary()
{
    //needed just to initialize the static variables
    //this method will be called form outside the library
    loaded = true;
}

}