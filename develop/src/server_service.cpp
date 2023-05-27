#include "socket.h"
#include "server.h"

int main(int argc, char *argv[])
{
    int w_addr, c_sock;
    struct sockaddr_in a_addr;
    std::string server_addr;
    int server_port;

    server_addr = "127.0.0.1";
    server_port = 8080;
#if 0
    if (argc == 2) {
        printf("argument size %d\n", argc);
        server_addr = argv[1];
    } else if (argc == 3) {
        printf("argument size %d\n", argc);
        server_addr = argv[1];
        server_port = atoi(argv[2]);
    }
#else
    if (argc == 2) {
        printf("argc %d\n", argc);
        return 0;
    }
    int i = 1;
    while (i < argc) {
        std::string check = argv[i];
        i++;
        if (check == "-a") {
            server_addr = argv[i];
        } else if (check == "-p") {
            server_port = atoi(argv[i]);
        } else {
            return 0;
        }
        i++;
    }
#endif

    printf("IP Address %s\n", server_addr.c_str());
    printf("Port %d\n", server_port);

    /* 構造体を全て0にセット */
    memset(&a_addr, 0, sizeof(struct sockaddr_in));

    /* サーバーのIPアドレスとポートの情報を設定 */
    a_addr.sin_family = AF_INET;
    a_addr.sin_port = htons(server_port);
    a_addr.sin_addr.s_addr = inet_addr(server_addr.c_str());

    /* ソケットを作成 */
    w_addr = socket(AF_INET, SOCK_STREAM, 0);
    if (w_addr == -1) {
        printf("socket error\n");
        return -1;
    }

    /* ソケットに情報を設定 */
    if (bind(w_addr, (const struct sockaddr *)&a_addr, sizeof(a_addr)) == -1) {
        printf("bind error\n");
        close(w_addr);
        return -1;
    }

    /* ソケットを接続待ちに設定 */
    if (listen(w_addr, 3) == -1) {
        printf("listen error\n");
        close(w_addr);
        return -1;
    }

    Server server;
    while (1) {
        /* 接続要求の受け付け（接続要求くるまで待ち） */
        printf("Waiting connect...\n");
        c_sock = accept(w_addr, NULL, NULL);
        if (c_sock == -1) {
            printf("accept error\n");
            close(w_addr);
            return -1;
        }
        printf("Connected!!\n");

        /* 接続済のソケットでデータのやり取り */
        server.httpServer(c_sock);

        /* ソケット通信をクローズ */
        close(c_sock);

        /* 次の接続要求の受け付けに移る */
    }

    /* 接続待ちソケットをクローズ */
    close(w_addr);

    return 0;
}
