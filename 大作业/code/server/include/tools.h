#ifndef __TOOLS_H__
#define __TOOLS_H__
#include"bigInt.h"
//求两个大数的最大公约数,采用辗转相除法
BigInt gcd(const BigInt& m, const BigInt& n)
{
	if (n == 0)
		return m;
	else
		return gcd(n, m % n);
}

//用扩展欧几里德算法求乘法模逆
BigInt Extended_gcd(const BigInt& a, const BigInt& b, BigInt& x, BigInt& y)
{
	BigInt t, d;
	//如果一个操作数为零则无法进行除法运算
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

