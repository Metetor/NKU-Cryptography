#include"aes.h"
int test()
{
	AES aes;
	printf("请输入密钥:\n");
	scanf("%s", aes.aes_key);
	printf("请输入明文:\n");
	scanf("%s", aes.plain);
	aes.encrypt_cbc();
	aes.decrypt_cbc();
	return 0;
}