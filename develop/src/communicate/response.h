#pragma once

#include <sys/socket.h>

#include <iostream>
#include <string>
#include <vector>

#include "file.h"

#define SIZE (100*1024)

class ResponseData {

public:
    std::string message;
    std::string header;
    std::string header_field;
    std::string body;
};

class SendResponse {
public:
    // メッセージを送信する
    void sendResponseMessage(int connect_sock) {
        int size;
        LOG.INFO("Response Message : " + data.message);
        size = send(connect_sock, data.message.c_str(), data.message.size(), 0);
    }

    void createHeader() { data.header = "Content-Length: " + std::to_string(data.body.size()) + "\r\n"; }
    void createHeaderField(std::string result) { data.header_field = "HTTP/1.1 " + result + "\r\n" + data.header + "\r\n"; }

    int createBody(std::string file_path) {
        ReadFile reader;
        reader.Read(file_path);
        LOG.INFO("file_path : " + file_path);
        data.body = reader.FileDataRecord();
        if (data.body.size() == 0) {
            LOG.INFO("get FileSize error 404 Not Found");
            return 404;
        }
        return 200;
    }

    int createMessage(int status) {
        int size;
        if (status == 200) {
            // ヘッダーフィールドの作成
            createHeaderField("200 OK");

            // ヘッダーフィールドとボディをコピー
            data.message = data.header_field + data.body;
            size = data.message.size();
        } else if (status == 404) {
            // ヘッダーフィールドの作成
            createHeaderField("404 Not Found");

            // ヘッダーフィールドをコピー
            data.message = data.header_field;
            size = data.header_field.size();
        } else {
            // statusが200・404以外はこのプログラムで非サポート
            printf("Not support status(%d)\n", status);
            return -1;
        }
        return size;
    }

private:
    ResponseData data;
    Logger LOG;
};
