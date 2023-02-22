#ifndef __INIT_H__
#define __INIT_H__
#include"conf.h"
int WSAInit();
int SockInit();
void RSAInit();
void Init();
void PKInit(SOCKET sock);
#endif // !__INIT_H__

