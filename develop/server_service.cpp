#include <sys/socket.h>
#include <netinet/in.h>	
#include <arpa/inet.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <string>

#include "server_service.h"

unsigned int ServerService::getFileSize(const char *path)
{
    int size, read_size;
    char read_buf[SIZE];
    FILE *f;

    f = fopen(path, "rb");
    if (f == NULL) {
        return 0;
    }

    size = 0;
    do {
        read_size = fread(read_buf, 1, SIZE, f);
        size += read_size;
    } while(read_size != 0);

    fclose(f);

    return size;
}

int ServerService::recvRequestMessage()
{
    int recv_size;
    
    recv_size = recv(connect_sock, request_message, SIZE, 0);

    return recv_size;
}

int ServerService::parseRequestMessage()
{
    char *line;
    char *tmp_method;
    char *tmp_target;
    
    /* リクエストメッセージの１行目のみ取得 */
    line = strtok(request_message, "\n");

    /* " "までの文字列を取得しmethodにコピー */
    tmp_method = strtok(line, " ");
    if (tmp_method == NULL) {
        printf("get method error\n");
        return -1;
    }
    strcpy(method, tmp_method);

    /* 次の" "までの文字列を取得しtargetにコピー */
    tmp_target = strtok(NULL, " ");
    if (tmp_target == NULL) {
        printf("get target error\n");
        return -1;
    }
    strcpy(target, tmp_target);

    return 0;
}

int ServerService::getProcessing(char *file_path)
{
    FILE *f;
    int file_size;

    /* ファイルサイズを取得 */
    file_size = getFileSize(file_path);
    if (file_size == 0) {
        /* ファイルサイズが0やファイルが存在しない場合は404を返す */
        printf("getFileSize error\n");
        return 404;
    }

    /* ファイルを読み込んでボディとする */
    f = fopen(file_path, "r");
    fread(body, 1, file_size, f);
    fclose(f);

    return 200;
}

int ServerService::createResponseMessage(int status, unsigned int body_size)
{
    unsigned int no_body_len;
    unsigned int body_len;

    response_message[0] = '\0';

    if (status == 200) {
        /* レスポンス行とヘッダーフィールドの文字列を作成 */
        sprintf(response_message, "HTTP/1.1 200 OK\r\n%s\r\n", header_field);

        no_body_len = strlen(response_message);
        body_len = body_size;

        /* ヘッダーフィールドの後ろにボディをコピー */
        memcpy(&response_message[no_body_len], body, body_len);
    } else if (status == 404) {
        /* レスポンス行とヘッダーフィールドの文字列を作成 */
        sprintf(response_message, "HTTP/1.1 404 Not Found\r\n%s\r\n", header_field);

        no_body_len = strlen(response_message);
        body_len = 0;
    } else {
        /* statusが200・404以外はこのプログラムで非サポート */
        printf("Not support status(%d)\n", status);
        return -1;
    }

    return no_body_len + body_len;
}

int ServerService::sendResponseMessage()
{
    int send_size;
    send_size = send(connect_sock, response_message, response_size, 0);
    return send_size;
}

void ServerService::showMessage(char *message, unsigned int size)
{
/* コメントを外せばメッセージが表示される
    unsigned int i;

    printf("Show Message\n\n");

    for (i = 0; i < size; i++) {
        putchar(message[i]);
    }
    printf("\n\n");
*/
}

int ServerService::httpServer()
{
    char header_field[SIZE];
    int status;
    unsigned int file_size;

    while (1) {
        /* リクエストメッセージを受信 */
        request_size = recvRequestMessage();
        if (request_size == -1) {
            printf("recvRequestMessage error\n");
            break;
        }

        if (request_size == 0) {
            /* 受信サイズが0の場合は相手が接続閉じていると判断 */
            printf("connection ended\n");
            break;
        }

        /* 受信した文字列を表示 */
        showMessage(request_message, request_size);

        /* 受信した文字列を解析してメソッドやリクエストターゲットを取得 */
        if (parseRequestMessage() == -1) {
            printf("parseRequestMessage error\n");
            break;
        }

        /* メソッドがGET以外はステータスコードを404にする */
        if (strcmp(method, "GET") == 0) {
            if (strcmp(target, "/") == 0) {
                /* /が指定された時は/index.htmlに置き換える */
                strcpy(target, "/index.html");
            }

            /* GETの応答をするために必要な処理を行う */
            status = getProcessing(&target[1]);
        } else {
            status = 404;
        }

        /* ヘッダーフィールド作成(今回はContent-Lengthのみ) */
        file_size = getFileSize(&target[1]);
        sprintf(header_field, "Content-Length: %u\r\n", file_size);

        /* レスポンスメッセージを作成 */
        response_size = createResponseMessage(status, file_size);
        if (response_size == -1) {
            printf("createResponseMessage error\n");
            break;
        }

        /* 送信するメッセージを表示 */
        showMessage(response_message, response_size);

        /* レスポンスメッセージを送信する */
        sendResponseMessage();
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
        printf("Connected!!\n");

        /* 接続済のソケットでデータのやり取り */
        ServerService server_service;
        server_service.connect_sock = c_sock;
        server_service.httpServer();

        /* ソケット通信をクローズ */
        close(c_sock);

        /* 次の接続要求の受け付けに移る */
    }

    /* 接続待ちソケットをクローズ */
    close(w_addr);

    return 0;
}
