#include "init.h"
#include <stdio.h>
#include <iostream>
#include "aes.h"
using namespace std;
int main()
{
	AES aes;
	Init();
	//connect
	if (connect(sockClient, (SOCKADDR*)&addrSer, sizeof(SOCKADDR)) == -1)
		perror("connect");
	else
		printf("Connect to Server\n");
	PKInit();

	while (1)
	{
		memset(aes.plain, 0, sizeof(aes.plain));
		printf("请输入消息:");
		cin.getline(aes.plain, 1024, '\n');
		aes.encrypt_cbc();
		memset(sendBuffer, 0, sizeof(sendBuffer));
		memcpy(sendBuffer, aes.cipher, sizeof(aes.cipher));
		if (send(sockClient, sendBuffer, sizeof(sendBuffer), 0) == -1)
			perror("send");
		else
			printf("发送成功\n");
	}
	WSACleanup();
	system("pause");
}