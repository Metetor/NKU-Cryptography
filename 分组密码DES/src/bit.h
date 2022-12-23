#pragma once
#include<bitset>
using namespace std;
bitset<64> strTobitset(char s[8])
{
	bitset<64> binset;
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			binset[i * 8 + j] = (s[i] >> (7-j)) & 1;
		}
	}
	return binset;
}
void bitsetTohex(bitset<64> binset) {
	uint8_t sum;
	for (int i = 0; i < 8; i++)
	{
		sum = 0;
		for (int j = 7; j>=0; j--)
		{
			sum += binset[i * 8 + j] * pow(2, 7 - j);
		}
		printf("0x%X ", sum);
	}
	return;
}
void leftShift(bitset<28>& S, int bit) {
	bitset<28> tmp = S;
	for (int i = 0; i < 28; i++)
	{
		S[i] = tmp[(i + bit) % 28];
	}
}
