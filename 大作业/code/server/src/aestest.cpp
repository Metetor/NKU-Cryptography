#include"aes.h"
int test()
{
	AES aes;
	printf("��������Կ:\n");
	scanf("%s", aes.aes_key);
	printf("����������:\n");
	scanf("%s", aes.plain);
	aes.encrypt_cbc();
	aes.decrypt_cbc();
	return 0;
}