#include "httplib.h"
#include <iostream>

int main(void)
{
    httplib::Client cli("localhost", 1234);

    auto res = cli.Get("/hi");
    if (res && res->status == 200) {
        std::cout << res->body << std::endl;
    }
}
