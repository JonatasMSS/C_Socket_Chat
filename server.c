#include <WinSock2.h>
#include <WS2tcpip.h>
#include <stdio.h>
#include <string.h>
#include <process.h> // _beginthread
#define DEFAULT_BUFLEN 512
#pragma comment(lib,"Ws2_32.lib")

SOCKET ClientSocket;

// Thread que fica recebendo mensagens do cliente
void __cdecl recvThread(void* param) {
    char recvbuf[DEFAULT_BUFLEN];
    int iResult;

    while (1) {
        iResult = recv(ClientSocket, recvbuf, sizeof(recvbuf) - 1, 0);
        if (iResult > 0) {
            recvbuf[iResult] = '\0';
            printf("\nCliente: %s\nVocê: ", recvbuf);
            fflush(stdout);

            if (strcmp(recvbuf, "exit") == 0) {
                printf("\nCliente encerrou a conexão.\n");
                closesocket(ClientSocket);
                WSACleanup();
                exit(0);
            }
        } else {
            printf("\nConexão encerrada pelo cliente.\n");
            closesocket(ClientSocket);
            WSACleanup();
            exit(0);
        }
    }
}

int main() {
    WSADATA wsaData;
    int iResult;
    SOCKET ListenSocket = INVALID_SOCKET;
    struct addrinfo *result = NULL, hints;


    SetConsoleOutputCP(CP_UTF8); // Força saída UTF-8
    SetConsoleCP(CP_UTF8);       // Força entrada UTF-8

    // Inicializa Winsock
    iResult = WSAStartup(MAKEWORD(2,2), &wsaData);
    if (iResult != 0) {
        printf("WSAStartup failed: %d\n", iResult);
        return 1;
    }

    ZeroMemory(&hints, sizeof(hints));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = IPPROTO_TCP;
    hints.ai_flags = AI_PASSIVE;

    // Cria a porta
    iResult = getaddrinfo(NULL, "8080", &hints, &result);
    if (iResult != 0) {
        printf("getaddrinfo failed: %d\n", iResult);
        WSACleanup();
        return 1;
    }

    ListenSocket = socket(result->ai_family, result->ai_socktype, result->ai_protocol);
    if (ListenSocket == INVALID_SOCKET) {
        printf("socket failed: %ld\n", WSAGetLastError());
        freeaddrinfo(result);
        WSACleanup();
        return 1;
    }

    iResult = bind(ListenSocket, result->ai_addr, (int)result->ai_addrlen);
    if (iResult == SOCKET_ERROR) {
        printf("bind failed: %d\n", WSAGetLastError());
        freeaddrinfo(result);
        closesocket(ListenSocket);
        WSACleanup();
        return 1;
    }
    freeaddrinfo(result);

    iResult = listen(ListenSocket, SOMAXCONN);
    if (iResult == SOCKET_ERROR) {
        printf("listen failed: %d\n", WSAGetLastError());
        closesocket(ListenSocket);
        WSACleanup();
        return 1;
    }

    printf("Aguardando conexão na porta 8080...\n");

    ClientSocket = accept(ListenSocket, NULL, NULL);
    if (ClientSocket == INVALID_SOCKET) {
        printf("accept failed: %d\n", WSAGetLastError());
        closesocket(ListenSocket);
        WSACleanup();
        return 1;
    }

    printf("Cliente conectado!\n");
    closesocket(ListenSocket); // não precisamos mais do socket de escuta

    // Cria thread para receber mensagens
    _beginthread(recvThread, 0, NULL);

    // Loop principal envia mensagens
    char sendbuf[DEFAULT_BUFLEN];
    while (1) {
        printf("Você: ");
        fgets(sendbuf, sizeof(sendbuf), stdin);
        sendbuf[strcspn(sendbuf, "\n")] = '\0';

        if (strcmp(sendbuf, "exit") == 0) {
            send(ClientSocket, sendbuf, (int)strlen(sendbuf), 0);
            printf("Você encerrou a conexão.\n");
            break;
        }

        send(ClientSocket, sendbuf, (int)strlen(sendbuf), 0);
    }

    closesocket(ClientSocket);
    WSACleanup();
    return 0;
}
