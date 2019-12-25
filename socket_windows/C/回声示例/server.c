#include <stdio.h>
#include <winsock2.h>
#pragma comment (lib, "ws2_32.lib")

#define BUF_SIZE 100

int main(void)
{
    WSADATA wsadata;
    WSAStartup(MAKEWORD(2,2), &wsadata);

    //创建套接字
    SOCKET servSock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

    //绑定套接字
    struct sockaddr_in sockaddr;
    sockaddr.sin_family = AF_INET;
    sockaddr.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");     //网址
    sockaddr.sin_port = htons(1234);
    bind(servSock, (struct sockaddr*)&sockaddr, sizeof(sockaddr));

    //进入监听状态
    listen(servSock, 20);

    //接收客户端请求
    struct sockaddr_in clntaddr;
    int addrlen = sizeof(clntaddr);
    SOCKET  clntsock = accept(servSock, (struct sockaddr*)&clntaddr, &addrlen);
    printf("a connection from: %s \r\n", inet_ntoa(clntaddr.sin_addr));

    char buffer[BUF_SIZE] = {0};
    int strlen = recv(clntsock, buffer,BUF_SIZE, 0);
    printf("recv:%s\n", buffer);
    send(clntsock, buffer, strlen, 0);

    //关闭套接字
    closesocket(clntsock);
    closesocket(servSock);

    //中止DLL的使用
    WSACleanup();

    return 0;
}