#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#include <iostream>
#include <string>

#include "file.h"

#define SIZE (100*1024)

class RequestReciever {
public:
    // メッセージを受信し、データを受け取る
    int recieveMessage(int socket) {
        int http_status;
        connect_sock = socket;
        http_status = recvRequestMessage();
        if (http_status == 202) {
            parseMessage();
            http_status = checkMethodStatus();
            replaceTarget();
        }
        return http_status;  // if ok, http status 202.
    };

    // リクエストメッセージを受信する
    int recvRequestMessage() {
        message_size = recv(connect_sock, &chr_message, SIZE, 0);
        str_message = {chr_message};
        if (message_size == -1) {
            printf("recvRequestMessage error\n");
            return 406; // http status 406 Not Acceptable
        } else if (message_size == 0) {
            printf("connection 400 Bad Request\n");
            return 400; // http status 400 Bad Request
        } else {
            printf("recieve message ok\n");
        }
        return 202; // http status 202 Accepted
    };

    void parseMessage() {
        // methodの取得
        std::cout << "parse : " << str_message << std::endl;
        std::string line = str_message.substr(0, str_message.find("\n"));
        method = line.substr(0, line.find(" "));
        std::cout << "method : " << method << " size : " << method.size() << std::endl;

        // targetの取得
        line = line.substr(method.size() + 1);
        target = line.substr(0, line.find(" "));
        std::cout << "target : " << target << " size : " << target.size() << std::endl;
    }

    int checkMethodStatus() {
        if (method == "GET") {
            return 202; // http status 202 Accepted
        }
        return 405; // http status 405 Method Not Allowed
    }

    void replaceTarget() {
        if (target == "/") {
            target = "/index.html";
        }
    }

    std::string target;
private:
    // 接続ソケット
    int connect_sock;

    // リクエストメッセージ
    char chr_message[SIZE];
    std::string str_message;
    int message_size;

    std::string method;
    //std::string target;
};

class ResponseSender {
public:
    // メッセージを送信する
    void sendResponseMessage() {message_size = send(connect_sock, message, message_size, 0);};


    // リクエストに対する処理を行う（今回はGETのみ）
    int getProcessing(std::string file_path) {
        int http_status;
        ReadFile reader;

        // ファイルサイズを取得
        reader.Read(file_path);
        std::cout << "[DEBUG][LOG] filesize" << std::endl;
        body_size = reader.FileSize();
        if (body_size == 0) {
            printf("get FileSize error 404 Not Found\n");  // 404 Not Found
            return 404;
        }
        body = reader.FileDataRecord();
        return 201;
    };

    int createMessage(int status) {
        char header_field[SIZE];
        sprintf(header_field, "Content-Length: %u\r\n", body_size);

        unsigned int no_body_len;
        unsigned int body_len;

        message[0] = '\0';

        if (status == 201) {
            /* レスポンス行とヘッダーフィールドの文字列を作成 */
            sprintf(message, "HTTP/1.1 200 OK\r\n%s\r\n", header_field);

            no_body_len = strlen(message);
            body_len = body_size;

            /* ヘッダーフィールドの後ろにボディをコピー */
            memcpy(&message[no_body_len], body.c_str(), body_len);
        } else if (status == 404) {
            /* レスポンス行とヘッダーフィールドの文字列を作成 */
            sprintf(message, "HTTP/1.1 404 Not Found\r\n%s\r\n", header_field);

            no_body_len = strlen(message);
            body_len = 0;
        } else {
            /* statusが200・404以外はこのプログラムで非サポート */
            printf("Not support status(%d)\n", status);
            return -1;
        }

        return no_body_len + body_len;
    };

    // 接続ソケット
    int connect_sock;

    // 送信するメッセージ
    char message[SIZE];
    int message_size;
    
    // 送信するbody部分
    std::string body;
    int body_size;
};

class ServerService {
public:
    // HTTPサーバーの処理を行う関数
    int httpServer();

    // 接続済のソケット
    int connect_sock;
};
