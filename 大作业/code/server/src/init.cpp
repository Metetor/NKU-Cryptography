#include<iostream>
#include"init.h"
#include "prime.h"
#include "gen.h"
void convertBigInttoStr(BigInt n, char* s)
{
	for (int i = 0; i < n.len; i++)
	{
		*s++ = (char)n.data[i];
	}
}
int WSAInit() {
	WORD version = MAKEWORD(2, 2);
	WSAData wsadata;
	int error;
	error = WSAStartup(version, &wsadata);
	if (error != 0)
	{
		switch (error)
		{
		case WSASYSNOTREADY:
			printf("WSASYSNOTREADY");
			break;
		case WSAVERNOTSUPPORTED:
			printf("WSAVERNOTSUPPORTED");
			break;
		case WSAEINPROGRESS:
			printf("WSAEINPROGRESS");
			break;
		case WSAEPROCLIM:
			printf("WSAEPROCLIM");
			break;
		}
		return -1;
	}
	return 0;
}
int SockInit()
{
	sockServer = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
	addrSer.sin_family = AF_INET;
	addrSer.sin_port = ServerPort;
	addrSer.sin_addr.S_un.S_addr = ServerIP;

	if (bind(sockServer, (SOCKADDR*)&addrSer, sizeof(SOCKADDR)) == -1)
		return 0;
	else
		return 1;
}
void RSAInit()
{
	printf("����RSA��Կ��Կ\n");
	genPrime();
	//����������
	printf("��ʼ���ɴ�����p\n");
	BigInt p = GeneratePrime();
	p.display();

	BigInt q = GeneratePrime();
	q.display();

	/*printf("��Կn=p*q\n");*/

	n2 = p * q;

	BigInt t = (p - 1) * (q - 1);
	//y���ڲ�����չŷ��������㣬�洢tģe�ĳ˷���Ԫ
	BigInt y;

	BigInt temp;
	while (1)
	{
		//������t���ʵ�e
		e2.Random(false);
		while (!(gcd(e2, t) == 1))
		{
			e2.Random(false);
		}

		//����չŷ������㷨��ͼ���eģt�ĳ˷���Ԫ
		temp = Extended_gcd(e2, t, d, y);

		//e*dģt���Ϊ1��˵��dȷʵ��eģt�ĳ˷���Ԫ
		temp = (e2 * d) % t;
		if (temp == 1)
			break;
		//������������e
	}
}
void Init()
{
	if (!WSAInit())
		printf("[WSAInit,Success] WSA��ʼ���ɹ�\n");
	if (SockInit())
		printf("[SockInit,Success] Socket��ʼ���ɹ�\n");

	RSAInit();
	
	printf("RSA��ԿNbΪ:\n");
	n2.display();
	printf("RSA��ԿEbΪ:\n");
	e2.display();

	printf("˽ԿdΪ:\n");
	d.display();
	//������Կ
}
void PKInit(SOCKET sock)
{
	//����PKb
	recv(sock, (char*)&n1, sizeof(n1), 0);
	/*n1.display();*/
	recv(sock, (char*)&e1, sizeof(e1), 0);
	/*e1.display();*/
	//����PKa
	send(sock, (char*)&n2, sizeof(n2), 0);
	send(sock, (char*)&e2, sizeof(e2), 0);
	//����AES_k������
	BigInt tmp;
	recv(sock, (char*)&tmp, sizeof(tmp), 0);
	printf("���ܵ����ܺ��AES��Կ����ʼ����...\n");
	printf("����Ϊ��\n");
	tmp.display();
	//����
	AES_k = Power(tmp, d, n2);
	printf("���ܺ������(AES_k)Ϊ:\n");
	AES_k.display();
	printf("PKInit Success\n");
}