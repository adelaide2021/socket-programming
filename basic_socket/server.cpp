#include <stdio.h>
#include <string.h>
#include <stdlib.h>
// 提供对POSIX操作系统API（write, read等）的访问功能
#include <unistd.h>
// 提供IP地址转换函数
#include <arpa/inet.h>
// 提供socket函数及数据结构
#include <sys/socket.h>
// 定义数据结构，Internet address family - 互联网地址族
#include <netinet/in.h>

#define BUF_SIZE 100

int main() {
    // 通过socket函数创建socket，AF_INET表示使用IPv4地址，
    // SOCK_STREAM表示使用面向连接的socket
    // IPPROTO_TCP表示使用TCP协议
    int serv_sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

    // 将套接字和IP、端口绑定
    struct sockaddr_in serv_addr;
    memset(&serv_addr, 0, sizeof(serv_addr));
    // sin_family表示协议簇，一般用AF_INET表示TCP/IP协议
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    // htons是将整型变量从主机字节顺序转变成网络字节顺序
    serv_addr.sin_port = htons(1234);
    // socket() 函数确定了套接字的各种属性，bind() 函数让套接字与特定的IP地址和端口对应起来，这样客户端才能连接到该套接字。
    // IP地址和端口都保存在sockaddr_in结构体中
    bind(serv_sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr));

    // 进入监听状态，等待用户发起请求。
    // 程序一旦执行到 accept() 就会被阻塞（暂停运行），直到客户端发起请求。
    listen(serv_sock, 20);

    // 接收客户端请求
    struct sockaddr_in clnt_addr;
    socklen_t clnt_addr_size = sizeof(clnt_addr);
    int clnt_sock = accept(serv_sock, (struct sockaddr*)&clnt_addr, &clnt_addr_size);
    char buffer[BUF_SIZE];

    // 回声
    int strLen = recv(clnt_sock, buffer, BUF_SIZE, 0); //接收客户端发来的数据
    send(clnt_sock, buffer, strLen, 0); //将数据原样返回
/*
    // 向客户端发送数据
    char str[] = "Hello world, from Adelaide";
    // write() 函数用来向套接字文件中写入数据，也就是向客户端发送数据
    write(clnt_sock, str, sizeof(str));
*/
    // 关闭套接字
    close(clnt_sock);
    close(serv_sock);

    return 0;
}