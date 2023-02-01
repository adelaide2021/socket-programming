#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>

#define BUF_SIZE 100

int main() {
    int serv_sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

    struct sockaddr_in serv_addr;
    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    serv_addr.sin_port = htons(1234);
    bind(serv_sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr));

    listen(serv_sock, 20);

    // 接收客户端请求
    struct sockaddr_in clnt_addr;
    socklen_t clnt_addr_size = sizeof(clnt_addr);
    char buffer[BUF_SIZE] = {0}; //缓冲区
    while(1) {
        // accept() 返回一个新的套接字来和客户端通信，clnt_addr 保存了客户端的IP地址和端口号，而 serv_sock 是服务器端的套接字.
        int clnt_sock = accept(serv_sock, (struct sockaddr*)&clnt_addr, &clnt_addr_size);
        int str_len = recv(clnt_sock, buffer, BUF_SIZE, 0);

        send(clnt_sock, buffer, str_len, 0);

        close(clnt_sock);
    }
   
    close(serv_sock);

    return 0;
}