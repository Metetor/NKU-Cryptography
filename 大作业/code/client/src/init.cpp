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
	printf("生成RSA公钥密钥\n");
	genPrime();
	//产生大素数
	printf("开始生成大素数p\n");
	BigInt p = GeneratePrime();
	p.display();

	BigInt q = GeneratePrime();
	q.display();
	
	/*printf("公钥n=p*q\n");*/

	n1 = p * q;

	BigInt t = (p - 1) * (q - 1);
	//y用于参与扩展欧几里得运算，存储t模e的乘法逆元
	BigInt y;

	BigInt temp;
	while (1)
	{
		//产生与t互质的e
		e1.Random(false);
		while (!(gcd(e1, t) == 1))
		{
			e1.Random(false);
		}

		//用扩展欧几里德算法试图求出e模t的乘法逆元
		temp = Extended_gcd(e1, t, d, y);

		//e*d模t结果为1，说明d确实是e模t的乘法逆元
		temp = (e1 * d) % t;
		if (temp == 1)
			break;
		//否则重新生成e
	}
}
void Init()
{
	if (!WSAInit())
		printf("[WSAInit,Success] WSA初始化成功\n");
	if (SockInit())
		printf("[SockInit,Success] Socket初始化成功\n");

	RSAInit();
	printf("RSA公钥Na为:\n");
	n1.display();
	printf("RSA公钥Ea为:\n");
	e1.display();

	printf("私钥d为:\n");
	d.display();
}
void PKInit()
{
	//发送PKa
	printf("调用PKInit\n");
	n1.display();
	send(sockClient, (char*)&n1, sizeof(n1), 0);
	e1.display();
	send(sockClient, (char*)&e1, sizeof(e1), 0);
	//接收PKb
	recv(sockClient, (char*)&n2, sizeof(n2), 0);
	recv(sockClient, (char*)&e2, sizeof(e2), 0);

	//生成AES的密钥
	AES_k.Random(true);
	printf("AES的密钥AES_k为:\n");
	AES_k.display();
	//加密发送AES_k
	printf("使用RSA加密发送AES_k\n");
	BigInt tmp;
	tmp = Power(AES_k,e2,n2);
	printf("加密后的AES_k为:\n");
	tmp.display();
	send(sockClient, (char*)&tmp, sizeof(tmp), 0);

	printf("PKInit Success\n");
}