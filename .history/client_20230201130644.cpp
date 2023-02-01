#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

int main() {
    int sock = socket(AF_INET, SOCK_STREAM, 0);

    // 向服务器（特定的IP和端口）发起请求
    struct sockaddr_in serv_addr;
    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    serv_addr.sin_port = htons(1234);
    // 通过 connect() 向服务器发起请求，服务器的IP地址和端口号保存在 sockaddr_in 结构体中。直到服务器传回数据后，connect() 才运行结束。
    connect(sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr));

    // 读取服务器传回的数据
    char buffer[40];
    // 通过 read() 从套接字文件中读取数据
    read(sock, buffer, sizeof(buffer)-1);

    printf("Message from server: %s\n", buffer);

    close(sock);

    return 0;
}