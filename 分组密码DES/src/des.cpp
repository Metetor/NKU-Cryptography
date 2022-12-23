#include<iostream>
#include<string>
#include"DES.h"
#include"bit.h"
#include"data.h"
using namespace std;
bool cmp(unsigned char* a, unsigned char* b)
{
	if (sizeof(a) != sizeof(b) || sizeof(a) == 0)
		cout << "data error";
	bool flag = true;
	for (int i = 0; i < sizeof(a); i++)
	{
		if (int(a[i])!=int((unsigned char)b[i]))
		{
			cout << int(a[i]) << " " << int(b[i]);
			flag = false;
			break;
		}
	}
	if (flag)
		return true;
	else
		return false;
}
void avalancheTest(des_test_case c,int m){//雪崩效应检查
	cout << "m =0 change plaintext ；m=1，change key" << endl;
	cout << "改变位置   " << "密文改变bit数   "<<"mode   " <<"avg"<<endl;
	bitset<64> txt = strTobitset((char*)c.txt);
	bitset<64> key = strTobitset((char*)c.key);
	DES des;
	int ss=0;
	if (!m)
	{
		bitset<64> cipher0;
		cipher0 = des.encrypt(txt, key);
		int sum;
		for (int i = 0; i < 8; i++)
		{
			sum = 0;
			bitset<64> cipher1;
			txt[i] = ~txt[i];
			cipher1 = des.encrypt(txt, key);
			//统计比较
			for (int j = 0; j < 64; j++)
			{
				if (cipher0[j] != cipher1[j])
					sum++;
			}
			cout <<i << "            " << sum <<"              "<<m<< endl;
			ss += sum;
			txt[i] = ~txt[i];
		}
		cout << "                                   " << ss / 8 << endl;
		return;
	}
	bitset<64> cipher0;
	cipher0 = des.encrypt(txt, key);
	int sum;
	for (int i = 0; i < 9; i++)
	{
		if ((i + 1) % 8 == 0)
			continue;
		sum = 0;
		bitset<64> cipher1;
		key[i] = ~key[i];
		cipher1 = des.encrypt(txt, key);
		//统计比较
		for (int j = 0; j < 64; j++)
		{
			if (cipher0[j] != cipher1[j])
				sum++;
		}
		cout << i << "            " << sum << "              " << m << endl;
		ss += sum;
		key[i] = ~key[i];
	}
	cout << "                                   " << ss / 8 << endl;
	return;
}
int main() {

	for (int i = 0; i < 20; i++)
	{	
		DES des;
		bitset<64> txt = strTobitset((char*)cases[i].txt);
		bitset<64> key=strTobitset((char *)cases[i].key);
		char* out;
		bitset<64> cipher;
		if (cases[i].mode)
		{
			cipher=des.encrypt(txt, key);
			//输出16进制加密结果
			cout <<"第"<<i<<"组加密结果为:";
			bitsetTohex(cipher);	
			cout << endl;
		}		
		else
		{
			cipher= des.decrypt(txt, key);
			cout << "第" << i << "组解密结果为:";
			bitsetTohex(cipher);
			cout << endl;
		}
		bool flag = 1;
		bitset<64> bout = strTobitset((char*)cases[i].out);
		for (int i = 0; i < 64; i++)
		{
			if (cipher[i] != bout[i])
			{
				flag = 0;
				break;
			}
		}
		if (flag)
			cout << i << ":  true" << endl;
		else
			cout << i << ":  false"<<endl;
	}
	avalancheTest(cases[1], 1);

	//printf("%x", &s);
	//初始置换

	system("pause");
	return 0;
}
