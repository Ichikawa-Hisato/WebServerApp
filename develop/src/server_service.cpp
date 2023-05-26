#include "server_service.h"

int ServerService::httpServer()
{
    while (1) {
        int http_status;

        // データ受信
        LOG.INFO("waiting Recieve Request");
        RecieveRequest reciever;
        LOG.INFO("start Recieve Request");
        http_status = reciever.recieveRequestMessage(connect_sock);
        if (http_status == 200) {
            reciever.parseRecieveMessage();
            method = reciever.parseMethod();
            target = reciever.parseTarget();
            if (method == "GET") {
                if (target == "/") {
                    target = "/index.html";
                }
            }
            LOG.INFO("root ok");
        } else {
            LOG.INFO("recieve error");
            break;
        }

        //データ送信
        SendResponse sender;
        http_status = sender.createBody(target.substr(1));
        sender.createHeader();

        int message_size = sender.createMessage(http_status);
        if (message_size == -1) {
            LOG.INFO("createResponseMessage error");
            break;
        }

        sender.sendResponseMessage(connect_sock);
        //std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    }
    return 0;
}

int main(int argc, char *argv[])
{
    int w_addr, c_sock;
    struct sockaddr_in a_addr;
    std::string server_addr;
    int server_port;

    server_addr = "127.0.0.1";
    server_port = 8080;
    if (argc == 2) {
        printf("argument size %d\n", argc);
        server_addr = argv[1];
    } else if (argc == 3) {
        printf("argument size %d\n", argc);
        server_addr = argv[1];
        server_port = atoi(argv[2]);
    }
    printf("IP Address %s\n", server_addr.c_str());
    printf("Port %d\n", server_port);

    /* ソケットを作成 */
    w_addr = socket(AF_INET, SOCK_STREAM, 0);
    if (w_addr == -1) {
        printf("socket error\n");
        return -1;
    }

    /* 構造体を全て0にセット */
    memset(&a_addr, 0, sizeof(struct sockaddr_in));

    /* サーバーのIPアドレスとポートの情報を設定 */
    a_addr.sin_family = AF_INET;
    a_addr.sin_port = htons(server_port);
    a_addr.sin_addr.s_addr = inet_addr(server_addr.c_str());

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

    while (1) {
        /* 接続要求の受け付け（接続要求くるまで待ち） */
        printf("Waiting connect...\n");
        c_sock = accept(w_addr, NULL, NULL);
        if (c_sock == -1) {
            printf("accept error\n");
            close(w_addr);
            return -1;
        }
        printf("Connected!! socket: %d\n", c_sock);

        /* 接続済のソケットでデータのやり取り */
        ServerService server_service;
        server_service.connect_sock = c_sock;
        server_service.httpServer();

        /* ソケット通信をクローズ */
        printf("soket close\n");
        close(c_sock);

        /* 次の接続要求の受け付けに移る */
    }

    /* 接続待ちソケットをクローズ */
    close(w_addr);

    return 0;
}
