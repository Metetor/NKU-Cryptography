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
	printf("生成RSA公钥密钥\n");
	genPrime();
	//产生大素数
	printf("开始生成大素数p\n");
	BigInt p = GeneratePrime();
	p.display();

	BigInt q = GeneratePrime();
	q.display();

	/*printf("公钥n=p*q\n");*/

	n2 = p * q;

	BigInt t = (p - 1) * (q - 1);
	//y用于参与扩展欧几里得运算，存储t模e的乘法逆元
	BigInt y;

	BigInt temp;
	while (1)
	{
		//产生与t互质的e
		e2.Random(false);
		while (!(gcd(e2, t) == 1))
		{
			e2.Random(false);
		}

		//用扩展欧几里德算法试图求出e模t的乘法逆元
		temp = Extended_gcd(e2, t, d, y);

		//e*d模t结果为1，说明d确实是e模t的乘法逆元
		temp = (e2 * d) % t;
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
	
	printf("RSA公钥Nb为:\n");
	n2.display();
	printf("RSA公钥Eb为:\n");
	e2.display();

	printf("私钥d为:\n");
	d.display();
	//交换公钥
}
void PKInit(SOCKET sock)
{
	//接收PKb
	recv(sock, (char*)&n1, sizeof(n1), 0);
	/*n1.display();*/
	recv(sock, (char*)&e1, sizeof(e1), 0);
	/*e1.display();*/
	//发送PKa
	send(sock, (char*)&n2, sizeof(n2), 0);
	send(sock, (char*)&e2, sizeof(e2), 0);
	//接收AES_k并解密
	BigInt tmp;
	recv(sock, (char*)&tmp, sizeof(tmp), 0);
	printf("接受到加密后的AES密钥，开始解密...\n");
	printf("密文为：\n");
	tmp.display();
	//解密
	AES_k = Power(tmp, d, n2);
	printf("解密后的明文(AES_k)为:\n");
	AES_k.display();
	printf("PKInit Success\n");
}