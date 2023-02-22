#include"bigInt.h"
int prime[1000];
//Ĭ�Ϲ��캯��,��Ա������0
BigInt::BigInt()
{
	for (int i = 0; i < MAXSIZE; i++)
		data[i] = 0;
	pn = true;
	len = 0;
}


//��int��ʼ������
BigInt::BigInt(const int& a)
{
	for (int i = 0; i < MAXSIZE; i++)
		data[i] = 0;
	data[0] = a;
	if (a >= 0)
		pn = true;
	else
		pn = false;
	len = 1;
}

//�ô�����������ֵ
BigInt::BigInt(const BigInt& a)
{
	for (int i = 0; i < MAXSIZE; i++)
		data[i] = a.data[i];
	pn = a.pn;
	len = a.len;
}

//�ô�����������ֵ
void BigInt::operator= (const BigInt& a)
{
	for (int i = 0; i < MAXSIZE; i++)
		data[i] = a.data[i];
	pn = a.pn;
	len = a.len;
}

//�Ƚ����������Ĵ�С,a<b,������,���򷵻ؼ�
bool operator< (const BigInt& a, const BigInt& b)
{
	for (int i = MAXSIZE - 1; i > 0; i--)
	{
		if (a.data[i] < b.data[i])
			return true;
		if (a.data[i] > b.data[i])
			return false;
	}
	return a.data[0] < b.data[0];
}

//�Ƚ����������Ĵ�С,a>b,������,���򷵻ؼ�
bool operator> (const BigInt& a, const BigInt& b)
{
	for (int i = MAXSIZE - 1; i >= 0; i--)
	{
		if (a.data[i] > b.data[i])
			return true;
		if (a.data[i] < b.data[i])
			return false;
	}
	return false;
}

//�ж����������Ƿ����,��ȷ�����,���򷵻ؼ�
bool operator== (const BigInt& a, const BigInt& b)
{
	for (int i = 0; i < MAXSIZE; i++)
		if (a.data[i] != b.data[i])
			return false;
	return true;
}

//�ж�һ��������һ��intֵ�Ƿ����,��ȷ�����,���򷵻ؼ�
bool operator== (const BigInt& a, const int& b)
{
	for (int i = 1; i < a.GetLength(); i++)
		if (a.data[i] != 0)
			return false;
	return a.data[0] == b;
}

//�������������ĺ�,������ʽ��ӷ�
BigInt operator+ (const BigInt& a, const BigInt& b)
{
	BigInt result;
	//64λ����,���ÿ��λ����ӵ���ʱ��
	unsigned __int64 sum;
	//carryΪ��λ��־,subΪ��������������ʱ,���ÿ��λ���������ʱ��
	unsigned int carry = 0, sub;
	//ȡa,b�г��Ƚϳ��ĳ���
	int length = (a.GetLength() >= b.GetLength() ? a.GetLength() : b.GetLength());

	//������������ͬʱ,���мӷ�����
	if (a.pn == b.pn)
	{
		//ÿһλ������ʽ���
		for (int i = 0; i < length; i++)
		{
			sum = (unsigned __int64)a.data[i] + b.data[i] + carry;
			result.data[i] = (unsigned int)sum;
			//sum�ĸ�λΪ��λ
			carry = (sum >> 32);
		}

		result.pn = a.pn;
		return result;
	}

	//�������Ų�ͬʱ,���м�������
	else
	{
		BigInt tmp1, tmp2;

		//ȡ��a,b�о���ֵ�ϴ����Ϊ������
		if (a < b)
		{
			tmp1 = b;
			tmp2 = a;
		}
		else
		{
			tmp1 = a;
			tmp2 = b;
		}

		//ÿһλ������ʽ��
		for (int i = 0; i < length; i++)
		{
			sub = tmp2.data[i] + carry;
			if (tmp1.data[i] >= sub)
			{
				result.data[i] = tmp1.data[i] - sub;
				carry = 0;
			}
			else
			{
				//��λ��
				result.data[i] = (unsigned __int64)tmp1.data[i] + (1 << 32) - sub;
				carry = 1;
			}
		}
		result.pn = tmp1.pn;
		result.len = result.GetLength();
		return result;
	}
}

//�������������Ĳ�,������ʽ�����
BigInt operator- (const BigInt& a, const BigInt& b)
{
	BigInt result;
	//64λ����,���ÿ��λ����ӵ���ʱ��
	unsigned __int64 sum;
	//carryΪ��λ��־,subΪ��������������ʱ,���ÿ��λ���������ʱ��
	unsigned int c = 0, sub;

	//������ͬʱ,���м�������
	if (a.pn == b.pn)
	{
		BigInt tmp1, tmp2;

		//ȡ��a,b�о���ֵ�ϴ����Ϊ������
		if (a < b)
		{
			tmp1 = b;
			tmp2 = a;
			tmp1.pn = !tmp1.pn;
		}
		else
		{
			tmp1 = a;
			tmp2 = b;
		}

		//ÿһλ������ʽ��
		for (int i = 0; i < MAXSIZE; i++)
		{
			sub = tmp2.data[i] + c;
			if (tmp1.data[i] >= sub)
			{
				result.data[i] = tmp1.data[i] - sub;
				c = 0;
			}
			else
			{
				//��λ��
				result.data[i] = (unsigned __int64)tmp1.data[i] + (1 << 32) - sub;
				c = 1;
			}
		}
		result.pn = tmp1.pn;
		result.len = result.GetLength();
		return result;
	}

	//�������Ų�ͬʱ,���мӷ�����
	else
	{
		//ÿһλ������ʽ���
		for (int i = 0; i < MAXSIZE; i++)
		{
			sum = (unsigned __int64)a.data[i] + b.data[i] + c;
			result.data[i] = (unsigned int)sum;
			//sum�ĸ�λΪ��λ
			c = (sum >> 32);
		}
		result.pn = a.pn;
		result.len = result.GetLength();
		return result;
	}
}

//������һ��int��
BigInt operator- (const BigInt& a, const int& b)
{
	BigInt tmp(b);
	BigInt result = a - tmp;
	result.len = result.GetLength();
	return result;
}


//��������һ��INT��
BigInt operator* (const BigInt& a, const unsigned int& b)
{
	BigInt result;
	//���B����A��ÿһλ����ʱ��
	unsigned __int64 sum;
	//��Ž�λ
	unsigned int c = 0;

	for (int i = 0; i < MAXSIZE; i++)
	{
		sum = ((unsigned __int64)a.data[i]) * b + c;
		result.data[i] = (unsigned int)sum;
		//��λ��SUM�ĸ�λ��
		c = (sum >> 32);
	}
	result.pn = a.pn;
	result.len = result.GetLength();
	return result;
}

//�������,������ʽ��
BigInt operator* (const BigInt& a, const BigInt& b)
{
	//last�����ʽ��һ�еĻ�,temp��ŵ�ǰ�еĻ�
	BigInt result, last, tmp;
	//sum��ŵ�ǰ�д���λ�Ļ�
	unsigned __int64 sum;
	//��Ž�λ
	unsigned int c;

	//������ʽ��
	for (int i = 0; i < b.GetLength(); i++)
	{
		c = 0;
		//B��ÿһλ��A���
		for (int j = 0; j < a.GetLength() + 1; j++)
		{
			sum = ((unsigned __int64)a.data[j]) * (b.data[i]) + c;
			if ((i + j) < MAXSIZE)
				tmp.data[i + j] = (unsigned int)sum;
			c = (sum >> 32);
		}
		result = (tmp + last);
		last = result;
		tmp.Clear();
	}

	//�жϻ��ķ���
	if (a.pn == b.pn)
		result.pn = true;
	else
		result.pn = false;
	result.len = result.GetLength();
	return result;
}

//������,�������̳���,���ö��ֲ��ҷ��Ż�
BigInt operator/ (const BigInt& a, const BigInt& b)
{
	//mulΪ��ǰ����,low,highΪ���ֲ�������ʱ���õı�־
	unsigned int mul, low, high;
	//subΪ�����뵱ǰ���̵Ļ�,subsequentΪ��������һ���̵Ļ�
	//dividend�����ʱ������
	BigInt dividend, quotient, sub, subsequent;
	int lengtha = a.GetLength(), lengthb = b.GetLength();

	//���������С�ڳ���,ֱ�ӷ���0
	if (a < b)
	{
		if (a.pn == b.pn)
			quotient.pn = true;
		else
			quotient.pn = false;
		return quotient;
	}

	//�ѱ������������ĳ��ȴӸ�λ��λ
	int i;
	for (i = 0; i < lengthb; i++)
		dividend.data[i] = a.data[lengtha - lengthb + i];

	for (i = lengtha - lengthb; i >= 0; i--)
	{
		//���������С�ڳ���,������λ
		if (dividend < b)
		{
			for (int j = lengthb; j > 0; j--)
				dividend.data[j] = dividend.data[j - 1];
			dividend.data[0] = a.data[i - 1];
			continue;
		}

		low = 0;
		high = 0xffffffff;

		//���ֲ��ҷ���������
		while (low < high)
		{
			mul = (((unsigned __int64)high) + low) / 2;
			sub = (b * mul);
			subsequent = (b * (mul + 1));

			if (((sub < dividend) && (subsequent > dividend)) || (sub == dividend))
				break;
			if (subsequent == dividend)
			{
				mul++;
				sub = subsequent;
				break;
			}
			if ((sub < dividend) && (subsequent < dividend))
			{
				low = mul;
				continue;
			}
			if ((sub > dividend) && (subsequent > dividend))
			{
				high = mul;
				continue;
			}

		}

		//���̽�����浽����ȥ
		quotient.data[i] = mul;
		//��ʱ��������Ϊ�����������̻��Ĳ�
		dividend = dividend - sub;

		//��ʱ����������λ
		if ((i - 1) >= 0)
		{
			for (int j = lengthb; j > 0; j--)
				dividend.data[j] = dividend.data[j - 1];
			dividend.data[0] = a.data[i - 1];
		}
	}

	//�ж��̵ķ���
	if (a.pn == b.pn)
		quotient.pn = true;
	else
		quotient.pn = false;
	quotient.len = quotient.GetLength();
	return quotient;
}

//������ģ����,�������������
BigInt operator% (const BigInt& a, const BigInt& b)
{
	unsigned int mul, low, high;
	BigInt dividend, quotient, sub, subsequent;
	int lengtha = a.GetLength(), lengthb = b.GetLength();

	//���������С�ڳ���,���ر�����Ϊģ
	if (a < b)
	{
		dividend = a;
		//����������Զ�뱻������ͬ
		dividend.pn = a.pn;
		return dividend;
	}

	//���г�������
	int i;
	for (i = 0; i < lengthb; i++)
		dividend.data[i] = a.data[lengtha - lengthb + i];

	for (i = lengtha - lengthb; i >= 0; i--)
	{
		if (dividend < b)
		{
			for (int j = lengthb; j > 0; j--)
				dividend.data[j] = dividend.data[j - 1];
			dividend.data[0] = a.data[i - 1];
			continue;
		}

		low = 0;
		high = 0xffffffff;

		while (low <= high)
		{
			mul = (((unsigned __int64)high) + low) / 2;
			sub = (b * mul);
			subsequent = (b * (mul + 1));

			if (((sub < dividend) && (subsequent > dividend)) || (sub == dividend))
				break;
			if (subsequent == dividend)
			{
				mul++;
				sub = subsequent;
				break;
			}
			if ((sub < dividend) && (subsequent < dividend))
			{
				low = mul;
				continue;
			}
			if ((sub > dividend) && (subsequent > dividend))
			{
				high = mul;
				continue;
			}
		}

		quotient.data[i] = mul;
		dividend = dividend - sub;
		if ((i - 1) >= 0)
		{
			for (int j = lengthb; j > 0; j--)
				dividend.data[j] = dividend.data[j - 1];
			dividend.data[0] = a.data[i - 1];
		}
	}

	//��ʱ��������Ϊ����ģ
	dividend.pn = a.pn;
	dividend.len = dividend.GetLength();
	return dividend;
}
//����һ���������,if small=false ������LENGTHΪSIZE��1/4;small=true,������LENGTHΪSIZE��1/8
void BigInt::Random(bool small)
{
	if (small == false)
	{
		for (int i = 0; i < (MAXSIZE / 4); i++)
			//����RAND()���ֻ�ܲ���0X7FFF����,Ϊ���ܲ���32λ�������,��Ҫ
			//3��RAND()����
			data[i] = (rand() << 17) + (rand() << 2) + (rand());
	}
	else
	{
		for (int i = 0; i < (MAXSIZE / 16); i++)
			//����RAND()���ֻ�ܲ���0X7FFF����,Ϊ���ܲ���32λ�������,��Ҫ
			//3��RAND()����
			data[i] = (rand() << 17) + (rand() << 2) + (rand());
	}
	len = this->GetLength();
}

//��������16������ʾ����Ļ��
void BigInt::display() const
{
	unsigned int temp, result;
	unsigned int an = 0xf0000000;

	for (int i = len - 1; i >= 0; i--)
	{
		temp = data[i];
		//������ÿһλ����ת����16�������
		for (int j = 0; j < 8; j++)
		{
			result = temp & an;
			result = (result >> 28);
			temp = (temp << 4);
			if (result >= 0 && result <= 9)
				cout << result;
			else
			{
				switch (result)
				{
				case 10:
					cout << "A";
					break;
				case 11:
					cout << "B";
					break;
				case 12:
					cout << "C";
					break;
				case 13:
					cout << "D";
					break;
				case 14:
					cout << "E";
					break;
				case 15:
					cout << "F";
					break;
				}
			}
		}
		cout << " ";
		if (i == len / 2)
			cout << endl;
	}
	cout << endl;
}

//��������������������
void BigInt::Output(ostream& out) const
{
	unsigned int temp, result;
	unsigned int an = 0xf0000000;

	for (int i = len - 1; i >= 0; i--)
	{
		temp = data[i];
		//������ÿһλ����ת����16�������
		for (int j = 0; j < 8; j++)
		{
			result = temp & an;
			result = (result >> 28);
			temp = (temp << 4);
			if (result >= 0 && result <= 9)
				out << result;
			else
			{
				switch (result)
				{
				case 10:
					out << "A";
					break;
				case 11:
					out << "B";
					break;
				case 12:
					out << "C";
					break;
				case 13:
					out << "D";
					break;
				case 14:
					out << "E";
					break;
				case 15:
					out << "F";
					break;
				}
			}
		}
	}
	out << endl;
}

//�������������
ostream& operator<< (ostream& out, const BigInt& x)
{
	x.Output(out);
	return out;
}

//������0
void BigInt::Clear()
{
	for (int i = 0; i < MAXSIZE; i++)
		data[i] = 0;
}

//���ش�������
inline int BigInt::GetLength() const
{
	int length = MAXSIZE;
	for (int i = MAXSIZE - 1; i >= 0; i--)
	{
		//��һλ��Ϊ0��ΪLENGTH
		if (data[i] == 0)
			length--;
		else
			break;
	}
	return length;
}

//������λ������,������Nλ
void BigInt::operator>> (const int& a)
{
	unsigned int bit;
	data[0] = (data[0] >> a);
	for (int i = 1; i < len; i++)
	{
		//�Ƚ�ÿһλ�ĵ�λ�Ƶ�BIT��
		bit = data[i] & 1;
		//�ٰ�BIT�Ƶ���һλ�ĸ�λ��
		bit = bit << (32 - a);;
		data[i - 1] = data[i - 1] | bit;
		data[i] = (data[i] >> a);
	}
	len = this->GetLength();
}

//�жϴ�����һ��INT�Ĵ�С
bool operator<= (const BigInt& a, const int& b)
{
	for (int i = 1; i < a.GetLength(); i++)
	{
		if (a.data[i] != 0)
			return false;
	}
	if (a.data[0] <= b)
		return true;
	else
		return false;
}


//���������㡪������n��p����ģm
//����Montgomery�㷨��
BigInt Power(const BigInt& n, const BigInt& p, const BigInt& m)
{
	BigInt temp = p;
	BigInt base = n % m;
	BigInt result(1);

	//���ָ��p�Ķ�������ʽ��ÿһλ
	while (!(temp <= 1))
	{
		//�����λΪ1�����ʾ��λ��Ҫ����ģ����
		if (temp.IsOdd())
		{
			result = (result * base) % m;
		}
		base = (base * base) % m;
		temp >> 1;
	}
	return (base * result) % m;
}


//������ɸ�飬����һ����������,���ܱ�С��5000����������
void pTabScr(BigInt& n)
{
	int i = 0;
	BigInt divisor;
	const int length = sizeof(prime) / sizeof(int);

	while (i != length)
	{
		n.Random(false);
		while (!n.IsOdd())
			n.Random(false);

		i = 0;
		for (; i < length; i++)
		{
			divisor = prime[i];
			if ((n % divisor) == 0)
				break;
		}
	}
}