#ifndef __CONF_H__
#define __CONF_H__
#include<winsock.h>
#include "bigInt.h"
#pragma comment(lib,"ws2_32.lib")
#define MAXLEN 1024
extern DWORD ClientIP, ServerIP;
extern u_short ClientPort, ServerPort;
extern SOCKET sockClient, sockServer;
extern SOCKADDR_IN addrCli, addrSer;
extern char recvBuffer[1024];
extern BigInt n1, e1;
extern BigInt n2, e2;
extern BigInt d;
extern BigInt AES_k;
#endif // !__CONF_H__

