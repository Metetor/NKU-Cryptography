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
	sockClient = socket(AF_INET, SOCK_STREAM, 0);
	addrCli.sin_family = AF_INET;
	addrCli.sin_port = ClientPort;
	addrCli.sin_addr.S_un.S_addr = ClientIP;

	sockServer = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
	addrSer.sin_family = AF_INET;
	addrSer.sin_port = ServerPort;
	addrSer.sin_addr.S_un.S_addr = ServerIP;

	if(bind(sockClient,(SOCKADDR*)&addrCli,sizeof(SOCKADDR))==-1)
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

	n1 = p * q;

	BigInt t = (p - 1) * (q - 1);
	//y���ڲ�����չŷ��������㣬�洢tģe�ĳ˷���Ԫ
	BigInt y;

	BigInt temp;
	while (1)
	{
		//������t���ʵ�e
		e1.Random(false);
		while (!(gcd(e1, t) == 1))
		{
			e1.Random(false);
		}

		//����չŷ������㷨��ͼ���eģt�ĳ˷���Ԫ
		temp = Extended_gcd(e1, t, d, y);

		//e*dģt���Ϊ1��˵��dȷʵ��eģt�ĳ˷���Ԫ
		temp = (e1 * d) % t;
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
	printf("RSA��ԿNaΪ:\n");
	n1.display();
	printf("RSA��ԿEaΪ:\n");
	e1.display();

	printf("˽ԿdΪ:\n");
	d.display();
}
void PKInit()
{
	//����PKa
	printf("����PKInit\n");
	n1.display();
	send(sockClient, (char*)&n1, sizeof(n1), 0);
	e1.display();
	send(sockClient, (char*)&e1, sizeof(e1), 0);
	//����PKb
	recv(sockClient, (char*)&n2, sizeof(n2), 0);
	recv(sockClient, (char*)&e2, sizeof(e2), 0);

	//����AES����Կ
	AES_k.Random(true);
	printf("AES����ԿAES_kΪ:\n");
	AES_k.display();
	//���ܷ���AES_k
	printf("ʹ��RSA���ܷ���AES_k\n");
	BigInt tmp;
	tmp = Power(AES_k,e2,n2);
	printf("���ܺ��AES_kΪ:\n");
	tmp.display();
	send(sockClient, (char*)&tmp, sizeof(tmp), 0);

	printf("PKInit Success\n");
}