#include <iostream>
#include "idevicecpp/idevicecpp.h"
#include <openssl/x509.h>

#ifdef idevicecpp
int main(int, char**)
{
    X509_new();
   std::cout << "Hello, world!\n";
}
#endif
