#include<winsock.h>
#include<windows.h>
#include "bigInt.h"
#pragma comment(lib,"ws2_32.lib")
DWORD ClientIP = inet_addr("127.0.0.1");
DWORD ServerIP = inet_addr("127.0.0.2");
u_short ClientPort = htons(11111);
u_short ServerPort = htons(22222);
SOCKET sockClient;
SOCKET sockServer;
SOCKADDR_IN  addrCli;
SOCKADDR_IN addrSer;
char recvBuffer[1024];
//¹«Ô¿ºÍË½Ô¿
BigInt n1, e1;
BigInt n2, e2;
BigInt d;
BigInt AES_k;