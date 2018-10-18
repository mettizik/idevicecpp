#include <iostream>
#include "idevicecpp/idevicecpp.h"
#include <plist/plist.h>
#include <usbmuxd.h>

#ifdef idevicecpp
int main(int, char**)
{
    usbmuxd_connect(0,0);
    plist_new_bool(1);
   std::cout << "Hello, world!\n";
}
#endif
