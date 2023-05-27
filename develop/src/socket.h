#pragma once

#include <iostream>

#define INVALID (-1)

#include "server.h"

class Socket {
private:
    Server server;
    struct sockaddr_in a_addr;
public:
    Socket(std::string address, int port) {
        a_addr.sin_family = AF_INET;
        a_addr.sin_port = htons(server_port);
        a_addr.sin_addr.s_addr = inet_addr(server_addr.c_str());
    };
    ~Socket(){};

    // ソケットを作成
    createSocket() {
        int socket;
        socket = socket(a_addr.sin_family, SOCK_STREAM, 0);
        if (listen(socket) == INVALID) {
            close(w_addr);
            return -1;
        }

        while (1) {
            if (connection(socket) == INVALID) {
                close(w_addr);
                return -1;
            }
        }
        close(w_addr);
        return 0;
    }

    // ソケットを接続待ちに設定
    int listen(int w_socket) {
        // ソケットに情報を設定
        if (bind(w_socket, (const struct sockaddr *)&a_addr, sizeof(a_addr)) == INVALID) {
            printf("bind error\n");
            return INVALID;
        }

        // ソケットを接続待ちに設定
        if (listen(w_socket, 5) == INVALID) {
            printf("listen error\n");
            return INVALID;
        }
        return 0;
    }

    int connection(int w_socket) {
        int c_sock;
        printf("Waiting connect...\n");
        c_sock = accept(w_socket, NULL, NULL);
        if (c_sock == INVALID) {
            printf("accept error\n");
            return INVALID;
        }
        printf("Connected!!\n");

        // 接続済のソケットでデータのやり取り
        server.httpServer(c_sock);

        printf("DisConnected!!\n");
        close(c_sock);
    }
}