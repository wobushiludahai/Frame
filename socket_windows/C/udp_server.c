/*
 * @Description: socket udp server
 * @Author: land sea
 * @Date: 2019-12-25 18:42:56
 * @LastEditTime: 2019-12-25 19:07:34
 * @LastEditors: Please set LastEditors
 */
#include <stdio.h>
#include <winsock2.h>
#pragma comment (lib, "ws2_32.lib")     //加载ws2_32.dll

#define BUF_SIZE 100

int main(void)
{
    WSADATA wsadata;
    WSAStartup(MAKEWORD(2, 2), &wsadata);

    //创建套接字
    SOCKET sock = socket(AF_INET, SOCK_STREAM, 0);

    //绑定套接字
    struct sockaddr_in servaddr;
    servaddr.sin_family = PF_INET;
    servaddr.sin_addr.S_un.S_addr = htonl(INADDR_ANY);  //自动获取IP地址
    servaddr.sin_port = htons(1234);
    bind(sock, (struct sockaddr*)&servaddr, sizeof(servaddr));

    //接收客户端请求
    struct sockaddr_in clntaddr;
    int clntsize = sizeof(clntaddr);
    char buffer[BUF_SIZE] = {0};
    while (1)
    {
        recvfrom(sock, buffer, BUF_SIZE, 0, (struct sockaddr*)&clntaddr, &clntsize);
        sendto(sock, buffer, strlen(buffer), 0, (struct sockaddr*)&clntaddr, clntsize);
    }

    closesocket(sock);
    WSACleanup();

    return 0;
}