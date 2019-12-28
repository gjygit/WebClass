#include <stdio.h>
#include <winsock.h>
#include "windows.h"

#pragma comment(lib, "ws2_32.lib")

void TCPServer() {
    SOCKET socketServer = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (INVALID_SOCKET == socketServer) {
        return;
    }
    struct sockaddr_in serverAddress = {};
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(5678);
    serverAddress.sin_addr.S_un.S_addr = htonl(INADDR_ANY);
    bind(socketServer, (struct sockaddr *) &serverAddress, sizeof(serverAddress));
    listen(socketServer, SOMAXCONN);
    printf("Waiting for client.......\n");
    struct sockaddr_in clientAddress = {};
    int nLen = sizeof(clientAddress);
    SOCKET socketClient = accept(socketServer, (struct sockaddr *) &clientAddress, &nLen);//�������Ӻ���
    printf("Client is connected\n");
    char buffRecv[100] = "";
    char buffSend[100] = "";
    while (recv(socketClient, buffRecv, 100, 0)) {
        printf("%s\n", buffRecv);
        scanf("%s", buffSend);
        send(socketClient, buffSend, sizeof(buffSend), 0);
    }
    closesocket(socketClient);
    closesocket(socketServer);
}

int main(int argc, char *argv[]) {
    WSADATA wsa = {0};
    WSAStartup(MAKEWORD(2, 2), &wsa);
    TCPServer();
    WSACleanup();
    return 0;
}
