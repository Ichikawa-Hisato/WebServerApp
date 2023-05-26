#include <sys/socket.h>
#include <netinet/in.h>	
#include <arpa/inet.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <map>
#include <regex>


#define INVALID (-1)
#define SIZE (6*1024)

struct Request {
    std::string request;
    std::string target;
    std::string method;
};

struct Response {
    std::string response;
    std::map<std::string, std::string> header;
    std::string body;
};

class Server {
public:
    int sock;

    // リクエストメッセージを受信する
    inline int recvRequestMessage(char *request_message, unsigned int buf_size) {
        return recv(sock, request_message, buf_size, 0);
    }

    inline int parseRequestMessage(char *method, char *target, char *request_message) {
        const char *delimiters = " \t\r\n"; // 区切り文字
        char *line;

        /* リクエストメッセージの１行目のみ取得 */
        line = strtok(request_message, "\n");

        /* " "までの文字列を取得しmethodにコピー */
        char *token = strtok(line, delimiters);
        if (token == nullptr) {
            std::cerr << "get method error" << std::endl;
            return -1;
        }
        std::strcpy(method, token);

        /* 次の" "までの文字列を取得しtargetにコピー */
        token = strtok(nullptr, delimiters);
        if (token == nullptr) {
            std::cerr << "get target error" << std::endl;
            return -1;
        }
        std::strcpy(target, token);

        return 0;
    }

    // リクエストに対する処理を行う（今回はGETのみ）
    inline int readFile(char *body, char *file_path) {
        std::ifstream ifs(file_path, std::ios::binary); // バイナリモードでファイルを開く
        std::stringstream file_data;

        if (!ifs) {
            std::cerr << "Failed to open file." << std::endl;
            return 404;
        }

        file_data << ifs.rdbuf(); // ファイルデータを一度に読み込む

        if (file_data.str().empty()) {
            std::cerr << "File size error." << std::endl;
            return 404;
        }

        const std::string& file_str = file_data.str();
        std::memcpy(body, file_str.c_str(), file_str.size() + 1); // null 終端文字のため +1

        return 200;
    }

    // レスポンスのヘッダーを作成
    inline std::string createHeader(int statusCode, const std::map<std::string, std::string>& header) {
        std::string headerString;
        headerString.reserve(256); // 予想されるヘッダーサイズに合わせて適切な値を指定
        // ステータスコードとステータスメッセージを作成
        headerString += "HTTP/1.1 " + std::to_string(statusCode) + " " + status_message(statusCode) + "\r\n";

        // ヘッダーフィールドの追加
        for (const auto& pair : header) {
            headerString += pair.first + ": " + pair.second + "\r\n";
        }

        // ヘッダーフィールドの終端を示す空行を追加
        headerString += "\r\n";

        return headerString;
    }

    inline std::string status_message(int status)
    {
        switch (status) {
        case 200: return "OK";
        case 400: return "Bad Request";
        case 404: return "Not Found";
        case 415: return "Unsupported Media Type";
        default:
            case 500: return "Internal Server Error";
        }
    }

    // レスポンスを作成する
    inline int createResponse(char *response_message, int status, char *body, char *path) {
        Response res;
        std::string header;

        res.header["Content-Type"] = find_content_type(path);
        res.header["Content-Length"] = std::to_string(strlen(body));
        res.header["Connection"] = "keep-alive";

        header = createHeader(status, res.header);

        std::string response;
        response.reserve(header.size() + strlen(body));
        response += header;
        response += body;

        std::memcpy(response_message, response.c_str(), response.size() + 1); // null 終端文字のため +1

        return 0;
    }

    inline const char* find_content_type(const std::string& path)
    {
        static const std::unordered_map<std::string, std::string> mimeTypes = {
            { "txt", "text/plain" },
            { "html", "text/html" },
            { "css", "text/css" },
            { "jpeg", "image/jpg" },
            { "jpg", "image/jpg" },
            { "png", "image/png" },
            { "gif", "image/gif" },
            { "svg", "image/svg+xml" },
            { "ico", "image/x-icon" },
            { "json", "application/json" },
            { "pdf", "application/pdf" },
            { "js", "application/javascript" },
            { "xml", "application/xml" },
            { "xhtml", "application/xhtml+xml" }
        };

        auto ext = file_extension(path);
        auto it = mimeTypes.find(ext);
        if (it != mimeTypes.end()) {
            return it->second.c_str();
        }

        return nullptr;
    }

    inline std::string file_extension(const std::string& path)
    {
        std::smatch m;
        auto pat = std::regex("\\.([a-zA-Z0-9]+)$");
        if (std::regex_search(path, m, pat)) {
            return m[1].str();
        }
        return std::string();
    }

    // レスポンスメッセージを送信する
    inline int sendResponse(char *response_message, unsigned int message_size) {
        return send(sock, response_message, message_size, 0);
    }
    inline int sendResponse(char *response_message) {
        return sendResponse(response_message, strlen(response_message));
    }

    // HTTPサーバーの処理を行う関数
    int httpServer(int _sock) {
        sock = _sock;

        int request_size, response_size;
        char request_message[SIZE];
        char response_message[SIZE];
        char method[SIZE];
        char target[SIZE];

        char body[SIZE];
        int status;

        while (1) {
            /* リクエストメッセージを受信 */
            request_size = recvRequestMessage(request_message, SIZE);
            if (request_size == INVALID) {
                printf("recvRequestMessage error\n");
                break;
            }

            if (request_size == 0) {
                /* 受信サイズが0の場合は相手が接続閉じていると判断 */
                printf("connection ended\n");
                break;
            }

            /* 受信した文字列を解析してメソッドやリクエストターゲットを取得 */
            if (parseRequestMessage(method, target, request_message) == -1) {
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
                printf("get target file : %s\n", target);
                status = readFile(body, &target[1]);
            } else {
                printf("404\n");
                status = 404;
            }

            if (createResponse(response_message, status, body, &target[1]) == INVALID) {
                printf("createResponseMessage error\n");
                break;
            }

            /* レスポンスメッセージを送信する */
            sendResponse(response_message);
        }
        return 0;
    }
};