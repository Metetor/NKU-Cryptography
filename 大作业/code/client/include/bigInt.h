#ifndef __BIGINT_H__
#define __BIGINT_H__
#include <iostream>
#include <stdlib.h> 
using namespace std;
extern int prime[1000];
const int MAXSIZE = 64;
class BigInt {
	friend BigInt operator+ (const BigInt&, const BigInt&);
	friend BigInt operator- (const BigInt&, const BigInt&);
	friend BigInt operator- (const BigInt&, const int&);
	friend BigInt operator* (const BigInt&, const BigInt&);
	friend BigInt operator* (const BigInt&, const unsigned int&);
	friend BigInt operator% (const BigInt&, const BigInt&);
	friend BigInt operator/ (const BigInt&, const BigInt&);
	friend bool operator< (const BigInt&, const BigInt&);
	friend bool operator> (const BigInt&, const BigInt&);
	friend bool operator<= (const BigInt&, const int&);
	friend bool operator== (const BigInt&, const BigInt&);
	friend bool operator== (const BigInt&, const int&);
	friend ostream& operator<< (ostream&, const BigInt&);
	friend BigInt Power(const BigInt&, const BigInt&, const BigInt&);//������
	friend void pTabScr(BigInt& n);
	friend void convertBigInttoStr(BigInt n, char* s);
public:
	BigInt();
	BigInt(const int&);
	BigInt(const BigInt&);

	void operator= (const BigInt&);
	void operator= (const int& a) { Clear(); data[0] = a; }
	void operator>> (const int&);

	inline int GetLength() const;   //���ش����ĳ���
	bool GetPN() { return pn; }  //�жϴ��������� 
	void Clear();  //������0
	//void Random(); //�������һ������
	void Random(bool s);  //�������һ����С�Ĵ���
	void display() const;
	void Output(ostream& out) const;
	bool IsOdd() const { return (data[0] & 1); }  //�жϴ�����ż��

public:
	unsigned int data[MAXSIZE];
	bool pn;
	int len;
};


#endif