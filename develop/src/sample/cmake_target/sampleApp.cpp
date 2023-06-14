#include <iostream>
#include "lib.h"

int main(void)
{
    std::cout << "Hello,World" << std::endl;

    Library lib;
    std::cout << lib.lib_string() << std::endl;
}
