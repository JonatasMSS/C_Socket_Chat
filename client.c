#include <WinSock2.h>
#include <WS2tcpip.h>
#include <stdio.h>
#include <string.h>
#include <process.h>   // para _beginthread
#define DEFAULT_BUFLEN 512
#pragma comment(lib,"Ws2_32.lib")

SOCKET ConnectSocket;

// Thread que só fica ouvindo o servidor
void __cdecl recvThread(void* param) {
    char recvbuf[DEFAULT_BUFLEN];
    int iResult;

    while (1) {
        iResult = recv(ConnectSocket, recvbuf, sizeof(recvbuf) - 1, 0);
        if (iResult > 0) {
            recvbuf[iResult] = '\0';
            printf("\nServidor: %s\nVocê: ", recvbuf);
            fflush(stdout);

            if (strcmp(recvbuf, "exit") == 0) {
                printf("\nServidor encerrou a conexão.\n");
                closesocket(ConnectSocket);
                WSACleanup();
                exit(0);
            }
        } else {
            printf("\nConexão encerrada pelo servidor.\n");
            closesocket(ConnectSocket);
            WSACleanup();
            exit(0);
        }
    }
}

int main(int argc, char **argv) {

    SetConsoleOutputCP(CP_UTF8); // Força saída UTF-8
    SetConsoleCP(CP_UTF8);       // Força entrada UTF-8
    WSADATA WSAData;
    int iResult;
    struct addrinfo *result = NULL, *ptr = NULL, hints;

    iResult = WSAStartup(MAKEWORD(2,2), &WSAData);
    if(iResult != 0){
        printf("Erro ao inicializar WSA: %d\n", iResult);
        return 1;
    }

    ZeroMemory(&hints, sizeof(hints));
    hints.ai_family   = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = IPPROTO_TCP;

    iResult = getaddrinfo(argv[1], argv[2], &hints, &result);
    if (iResult != 0) {
        printf("getaddrinfo failed: %d\n", iResult);
        WSACleanup();
        return 1;
    }

    ptr = result;
    ConnectSocket = socket(ptr->ai_family, ptr->ai_socktype, ptr->ai_protocol);
    if(ConnectSocket == INVALID_SOCKET){
        printf("Socket invalido: %ld\n", WSAGetLastError());
        freeaddrinfo(result);
        WSACleanup();
        return 1;
    }

    iResult = connect(ConnectSocket, ptr->ai_addr, (int)ptr->ai_addrlen);
    freeaddrinfo(result);
    if (iResult == SOCKET_ERROR) {
        printf("Falha ao conectar ao servidor.\n");
        closesocket(ConnectSocket);
        WSACleanup();
        return 1;
    }

    printf("Conectado ao servidor!\n");

    // Cria thread que só escuta o servidor
    _beginthread(recvThread, 0, NULL);

    // Thread principal: envia mensagens
    char sendbuf[DEFAULT_BUFLEN];
    while (1) {
        printf("Você: ");
        fgets(sendbuf, sizeof(sendbuf), stdin);
        sendbuf[strcspn(sendbuf, "\n")] = '\0';

        if (strcmp(sendbuf, "exit") == 0) {
            send(ConnectSocket, sendbuf, (int)strlen(sendbuf), 0);
            printf("Você encerrou a conexão.\n");
            break;
        }

        send(ConnectSocket, sendbuf, (int)strlen(sendbuf), 0);
    }

    closesocket(ConnectSocket);
    WSACleanup();
    return 0;
}
