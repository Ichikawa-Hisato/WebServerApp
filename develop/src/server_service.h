#pragma once

#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <unistd.h>

#include <iostream>
#include <string>
#include <thread>

#include "file.h"
#include "log.h"
#include "request.h"
#include "response.h"

#define SIZE (100*1024)

class ServerService {
public:
    // HTTPサーバーの処理を行う関数
    int httpServer();

    // 接続済のソケット
    int connect_sock;
private:
    Logger LOG;
    std::string method;
    std::string target;
};
