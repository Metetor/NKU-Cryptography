#ifndef __GEN_H__
#define __GEN_H__
#include <iostream>
#include "bigint.h"
#include"tools.h"
using namespace std;

//对大奇数n进行RabinMiller检测
bool RabinMiller(const BigInt& n)
{
	BigInt r, a, y;
	unsigned int s, j;
	r = n - 1;
	s = 0;

	while (!r.IsOdd())
	{
		s++;
		r >> 1;
	}

	//随机产生一个小于N-1的检测数a
	a.Random(true);

	//y = a的r次幂模n
	y = Power(a, r, n);

	//检测J=2至J<S轮
	if ((!(y == 1)) && (!(y == (n - 1))))
	{
		j = 1;
		while ((j <= s - 1) && (!(y == (n - 1))))
		{
			y = (y * y) % n;
			if (y == 1)
				return false;
			j++;
		}
		if (!(y == (n - 1)))
			return false;
	}
	return true;
}

//产生一个素数
BigInt GeneratePrime()
{
	BigInt n;
	int i = 0;

	//无限次循环，不断产生素数，直到i==5时（通过五轮RabinMiller测试）才会跳出while循环
	while (i < 5)
	{
		cout << "产生待测大奇数：" << endl;
		pTabScr(n);
		n.display();

		i = 0;
		//进行五轮RABINMILLER测试,五轮全部通过则素数合格
		for (; i < 5; i++)
		{
			if (!RabinMiller(n))
			{
				cout << "RABINMILLER测试失败" << endl;
				break;
			}
			cout << "RABINMILLER测试通过" << endl;
		}
	}
	return n;
}
#endif
