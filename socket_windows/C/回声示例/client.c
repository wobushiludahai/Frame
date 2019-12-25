#include <stdio.h>
#include <stdlib.h>
#include <winsock2.h>
#pragma comment(lib, "ws2_32.lib")  //加载ws2_32.dll

#define BUF_SIZE 100

int main(void)
{
    //初始化DLL
    WSADATA wsadata;
    WSAStartup(MAKEWORD(2, 2), &wsadata);

    //创建套接字
    SOCKET sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

    //向服务器发我请求
    struct sockaddr_in sockaddr;
    sockaddr.sin_family = PF_INET;
    sockaddr.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");
    sockaddr.sin_port = htons(1234);
    connect(sock, (struct sockaddr*)&sockaddr, sizeof(sockaddr));

    //获取用户输入的字符串
    char bufsend[BUF_SIZE] = {0};
    printf("Input a string:");
    gets(bufsend);
    send(sock, bufsend,strlen(bufsend), 0);
    //读取服务器回传数据
    char bufrecv[BUF_SIZE] = {0};
    recv(sock, bufrecv, BUF_SIZE, 0);
    printf("\nrecv:%s\n", bufrecv);

    //关闭套接字
    closesocket(sock);

    //中止使用DLL
    WSACleanup();

    return 0;
}