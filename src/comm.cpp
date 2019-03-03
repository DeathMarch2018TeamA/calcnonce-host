#include "comm.hpp"

#include <iostream>
#include <string>

#include <cstring>
#include <cstdlib>

extern "C" {

#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <netdb.h>

}

namespace {
    const int BUFFER_SIZE = 256;
    const std::string CONNECT_MESSAGE = "connection success";
    const std::string FINISH_MESSAGE  = "FINISH";

    int dstSocket;
    struct sockaddr_in dstAddr;
} // namespace 

namespace shigeCoin {

/* socket通信の初期化 */
bool initialize(const std::string teamname, const std::string IP_Address, const std::string port) {
    int read_size;
    struct hostent *hp;
    char buf[BUFFER_SIZE];
   
    // sockaddr_in 構造体のセット
    memset((char *)&dstAddr, 0, sizeof(dstAddr));
    dstAddr.sin_family = AF_INET;
    dstAddr.sin_port = htons(std::stoi(port));
    hp = gethostbyname(IP_Address.c_str());
    bcopy(hp->h_addr, &dstAddr.sin_addr, hp->h_length);

    // ソケットの作成
    dstSocket = socket(AF_INET, SOCK_STREAM, 0);

    // 接続
    if (connect(dstSocket, (struct sockaddr *)&dstAddr, sizeof(dstAddr)) < 0) {
        std::cout << IP_Address << "could not be connected" << std::endl;
        return false;
    }
    
    // 最初のメッセージを受け取る
    read_size = read(dstSocket, buf, BUFFER_SIZE);

    // メッセージが受け取れたらチーム名を送信
    if (std::string(buf) == CONNECT_MESSAGE) {
        std::cout << buf << std::endl;
        sendto(dstSocket, teamname.c_str(), teamname.length() + 1, 
           0, (struct sockaddr*)&dstAddr, sizeof(dstAddr));
        return true;
    } else {
        std::cout << "could not get the message" << std::endl;
        return false;
    }
}

/* 条件(0の個数)を受け取る */
const std::string get_zero(void) {
    char buf[BUFFER_SIZE];
    read(dstSocket, buf, sizeof(buf));
    return std::string(atoi(buf), '0');
}

/* ブロックを受け取る */
const std::string get_block(void) {
    char buf[BUFFER_SIZE];
    read(dstSocket, buf, sizeof(buf));
    return std::string(buf);
}

/* nonceを送る */
bool send_nonce(const std::string nonce) {
    int send_size = sendto(
        dstSocket, nonce.c_str(), nonce.length() + 1, 0,
        (struct sockaddr*)&dstAddr, sizeof(dstAddr)
    );
    return send_size >= 0;
}

/* 終了する */
bool finalize(void) {
    char buf[BUFFER_SIZE];
    read(dstSocket, buf, sizeof(buf));

    return ((std::string(buf) == FINISH_MESSAGE) && close(dstSocket) == 0);
}

}
