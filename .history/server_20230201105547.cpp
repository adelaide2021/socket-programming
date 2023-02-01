#include <stdio.h>
#include <string.h>
#include <stdlib.h>
// 提供对POSIX操作系统API的访问功能
#include <unistd.h>
// 提供IP地址转换函数
#include <arpa/inet.h>
// 提供socket函数及数据结构
#include <sys/socket.h>
定义数据结构
#include <netinet/in.h>

int main() {
    // 通过socket函数创建socket，AF_INET表示使用IPv4地址，
    // SOCK_STREAM表示使用面向连接的socket
    // IPPROTO_TCP表示使用TCP协议
    int serv_sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

    struct sockaddr_in serv_addr;
    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    serv_addr.sin_port = htons(1234);
    // 将套接字serv_sock与特定的IP地址和端口绑定，IP地址和端口都保存在sockaddr_in结构体中
    bind(serv_sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr));

    listen(serv_sock, 20);

    struct sockaddr_in clnt_addr;
    socklen_t clnt_addr_size = sizeof(clnt_addr);
    int clnt_sock = accept(serv_sock, (struct sockaddr*)&clnt_addr, &clnt_addr_size);

    char str[] = "http://c.biancheng.net/socket/";
    write(clnt_sock, str, sizeof(str));

    close(clnt_sock);
    close(serv_sock);

    return 0;
}