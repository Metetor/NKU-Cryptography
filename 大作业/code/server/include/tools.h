#ifndef __TOOLS_H__
#define __TOOLS_H__
#include"bigInt.h"
//���������������Լ��,����շת�����
BigInt gcd(const BigInt& m, const BigInt& n)
{
	if (n == 0)
		return m;
	else
		return gcd(n, m % n);
}

//����չŷ������㷨��˷�ģ��
BigInt Extended_gcd(const BigInt& a, const BigInt& b, BigInt& x, BigInt& y)
{
	BigInt t, d;
	//���һ��������Ϊ�����޷����г�������
	if (b == 0)
	{
		x = 1;
		y = 0;
		return a;
	}
	d = Extended_gcd(b, a % b, x, y);
	t = x;
	x = y;
	y = t - ((a / b) * y);
	return d;
}

#endif // !__TOOLS_H__

