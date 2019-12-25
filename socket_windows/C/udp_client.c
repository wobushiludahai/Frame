/*
 * @Description: socket udp client
 * @Author: land sea
 * @Date: 2019-12-25 18:42:46
 * @LastEditTime: 2019-12-25 19:07:11
 * @LastEditors: Please set LastEditors
 */
#include <stdio.h>
#include <stdlib.h>
#include <winsock2.h>
#pragma comment (lib, "ws2_32.lib")     //加载ws2_32.dll

#define BUF_SIZE 100

int main(void)
{
    WSADATA wsadata;
    WSAStartup(MAKEWORD(2, 2), &wsadata);

    //创建套接字
    SOCKET sock = socket(AF_INET, SOCK_STREAM, 0);

    //服务器地址信息
    struct sockaddr_in servaddr;
    servaddr.sin_family = PF_INET;
    servaddr.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");  //自动获取IP地址
    servaddr.sin_port = htons(1234);

    //不断获取用户输入然后发送给服务器，然后接收服务器信息
    struct sockaddr_in addr;
    int addrlen = sizeof(addr);
    while(1)
    {
        char buffer[BUF_SIZE] = {0};
        printf("Please Input a string: ");
        gets(buffer);
        sendto(sock, buffer, strlen(buffer), 0, (struct sockaddr*)&addr, addrlen);
        int strlen = recvfrom(sock, buffer, BUF_SIZE, 0, (struct sockaddr*)&addr, &addrlen);
        printf("\nrecv: %s\n", buffer);
    }
    
    closesocket(sock);
    WSACleanup();
    
    return 0;
}