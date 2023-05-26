#pragma once

#include <sys/socket.h>

#include <iostream>
#include <string>
#include <vector>

#define SIZE (100*1024)

class RequestData {
public:
    std::string message;
    std::vector<std::string> record;

    void parseMessage() {
        std::string line = message;
        while(line.find("\n") != std::string::npos) {
            record.push_back(line.substr(0, line.find("\n")));
            line = line.substr(0, line.find("\n"));
        }
    }
};

class RecieveRequest {
public:
    RecieveRequest() { LOG.INFO("######## start RecieveRequest ########"); }
    ~RecieveRequest() { LOG.INFO("######## end RecieveRequest ########"); }

    // リクエストメッセージを受信する
    int recieveRequestMessage(int connect_sock) {
        int size;
        char requestMessage[SIZE];
        LOG.INFO("connect soket : " + std::to_string(connect_sock));
        size = recv(connect_sock, requestMessage, SIZE, 0);
        data.message = {requestMessage};
        LOG.INFO("Recieve Message : " + data.message);

        if (size == -1) {
            printf("recvRequestMessage error\n");
            return 404;
        } else if (size == 0) {
            printf("connection bad request\n");
            return 404;
        } else {
            printf("recieve message ok\n");
        }
        return 200;
    }

    void parseRecieveMessage() { data.parseMessage();}

    std::string parseMethod() {
        std::string line = data.record[0];
        std::string method = line.substr(0, line.find(" "));
        return method;
    }
    std::string parseTarget() {
        std::string line = data.record[0];
        line = line.substr(line.find(" ") + 1);
        std::string target = line.substr(0, line.find(" "));
        return target;
    }

private:
    Logger LOG;
    RequestData data;
};
