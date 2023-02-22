#ifndef __GEN_H__
#define __GEN_H__
#include <iostream>
#include "bigint.h"
#include"tools.h"
using namespace std;

//�Դ�����n����RabinMiller���
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

	//�������һ��С��N-1�ļ����a
	a.Random(true);

	//y = a��r����ģn
	y = Power(a, r, n);

	//���J=2��J<S��
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

//����һ������
BigInt GeneratePrime()
{
	BigInt n;
	int i = 0;

	//���޴�ѭ�������ϲ���������ֱ��i==5ʱ��ͨ������RabinMiller���ԣ��Ż�����whileѭ��
	while (i < 5)
	{
		cout << "���������������" << endl;
		pTabScr(n);
		n.display();

		i = 0;
		//��������RABINMILLER����,����ȫ��ͨ���������ϸ�
		for (; i < 5; i++)
		{
			if (!RabinMiller(n))
			{
				cout << "RABINMILLER����ʧ��" << endl;
				break;
			}
			cout << "RABINMILLER����ͨ��" << endl;
		}
	}
	return n;
}
#endif
