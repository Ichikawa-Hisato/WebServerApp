#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#define SIZE (20*1024)

class ServerService {
public:
    /*
     * HTTPサーバーの処理を行う関数
     * 戻り値：0
     */
    int httpServer();

    /* 接続済のソケット */
    int connect_sock;
private:
    /*
     * リクエストメッセージを受信する
     * buf_size：そのバッファのサイズ
     * 戻り値：受信したデータサイズ（バイト長）
     */
    int recvRequestMessage();

    /*
     * リクエストメッセージを解析する（今回はリクエスト行のみ）
     * 戻り値：成功時は0、失敗時は-1
     */
    int parseRequestMessage();

    /*
     * リクエストに対する処理を行う（今回はGETのみ）
     * file_path：リクエストターゲットに対応するファイルへのパス
     * 戻り値：ステータスコード（ファイルがない場合は404）
     */
    int getProcessing(char *file_path);

    /*
     * レスポンスメッセージを作成する
     * status：ステータスコード
     * body_size：ボディのサイズ
     * 戻り値：レスポンスメッセージのデータサイズ（バイト長）
     */
    int createResponseMessage(int status, unsigned int body_size);

    /*
     * レスポンスメッセージを送信する
     * 戻り値：送信したデータサイズ（バイト長）
     */
    int sendResponseMessage();

    /* メッセージの表示 */
    void showMessage(char *message, unsigned int size);

    /* ファイルサイズを取得する */
    unsigned int getFileSize(const char *path);

    /* リクエストメッセージを格納するバッファへのアドレス */
    char request_message[SIZE];
    int request_size;

    /* 送信するレスポンスメッセージへのアドレス */
    char response_message[SIZE];
    int response_size;

    char method[SIZE];
    char target[SIZE];

    /* ヘッダーフィールドを格納したバッファへのアドレス */
    char header_field[SIZE];

    /* ボディを格納したバッファへのアドレス */
    char body[SIZE];
};
