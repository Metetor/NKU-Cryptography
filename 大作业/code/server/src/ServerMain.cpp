#include "init.h"
#include <stdio.h>
#include "aes.h"
int main()
{
	AES aes;
	int len = sizeof(SOCKADDR);
	Init();
	//��ʼ����
	if (listen(sockServer, 5) == -1) {
		perror("listen");
	}
	while (1)
	{
		SOCKET clientSock= accept(sockServer, (SOCKADDR*)&addrCli, &len);
		PKInit(clientSock);
		while (1)
		{
			memset(recvBuffer, 0, sizeof(recvBuffer));
			if (recv(clientSock, recvBuffer, sizeof(recvBuffer), 0) == -1)
				perror("recv");
			else
			{
				//��ʼ����
				memset(aes.cipher, 0, sizeof(aes.cipher));
				memcpy(aes.cipher, recvBuffer, sizeof(recvBuffer));
				printf("���ܵ�������Ϊ(16����):\n");
				for (int i = 0; i < strlen(aes.cipher); i++)
					printf("%x ", getIntFromChar(aes.cipher[i]));
				putchar('\n');
				aes.clen = strlen(aes.cipher);
				aes.decrypt_cbc();
			}
		}
	}
}
