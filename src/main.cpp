#include <iostream>
#include "idevicecpp/idevicecpp.h"
#include <plist/plist.h>

#ifdef idevicecpp
int main(int, char**)
{
    plist_new_bool(1);
   std::cout << "Hello, world!\n";
}
#endif
