#include <stdio.h>
#include "windows.h"
#include "winsock.h"

#pragma comment(lib, "ws2_32.lib")

void TCPClient() {
    SOCKET socketClient = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (INVALID_SOCKET == socketClient) {
        return;
    }
    struct sockaddr_in address = {0};
    address.sin_family = AF_INET;
    address.sin_port = htons(5678);
    address.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");
    if (SOCKET_ERROR == connect(socketClient, (struct sockaddr *) &address, sizeof(address))) {
        printf("Server connection failed!");
        closesocket(socketClient);
        return;
    }
    printf("Server connection succeeded!\n");
    char buffRecv[100] = "";
    char buffSend[100] = "";
    while (scanf("%s", buffSend) != EOF) {
        send(socketClient, buffSend, sizeof(buffSend), 0);
        recv(socketClient, buffRecv, 100, 0);
        printf("%s\n", buffRecv);
    }
    closesocket(socketClient);
}

int main(int argc, char *argv[]) {
    WSADATA wsa = {0};
    WSAStartup(MAKEWORD(2, 2), &wsa);
    TCPClient();
    WSACleanup();
    return 0;
}
