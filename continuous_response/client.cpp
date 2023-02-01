#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define BUF_SIZE 100

int main() {

    struct sockaddr_in serv_addr;
    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    serv_addr.sin_port = htons(1234);

    char buff_send[BUF_SIZE] = {0};
    char buff_recv[BUF_SIZE] = {0};

    while (1) {
        int sock = socket(AF_INET, SOCK_STREAM, 0);
        connect(sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr));
        
        printf("Input a string: ");
        gets(buff_send);
        send(sock, buff_send, strlen(buff_send), 0);

        recv(sock, buff_recv, BUF_SIZE, 0);
        printf("Messgae from server: %s\n", buff_recv);

        memset(buff_send, 0, BUF_SIZE);
        memset(buff_recv, 0, BUF_SIZE);
        
        close(sock);
    } 

    return 0;
}