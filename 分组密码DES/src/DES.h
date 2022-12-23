#pragma once
#include<string>
#include<bitset>
#include"bit.h"
using std::bitset;
string key;
class DES {
public:
	bitset<48> subKeys[16];//轮函数的子密钥
	const int ip[64]=  { 58, 50, 42, 34, 26, 18, 10, 2,
						 60, 52, 44, 36, 28, 20, 12, 4,
						 62, 54, 46, 38, 30, 22, 14, 6,
						 64, 56, 48, 40, 32, 24, 16, 8,
						 57, 49, 41, 33, 25, 17, 9,  1,
						 59, 51, 43, 35, 27, 19, 11, 3,
						 61, 53, 45, 37, 29, 21, 13, 5,
						 63, 55, 47, 39, 31, 23, 15, 7 };
	const int PC_1[56]= { 57, 49, 41, 33, 25, 17, 9,
						   1, 58, 50, 42, 34, 26, 18,
						  10,  2, 59, 51, 43, 35, 27,
						  19, 11,  3, 60, 52, 44, 36,
						  63, 55, 47, 39, 31, 23, 15,
						   7, 62, 54, 46, 38, 30, 22,
						  14,  6, 61, 53, 45, 37, 29,
						  21, 13,  5, 28, 20, 12,  4 };//PC_1置换表
	const int PC_2[56]= { 14, 17, 11, 24,  1,  5,
						   3, 28, 15,  6, 21, 10,
						  23, 19, 12,  4, 26,  8,
						  16,  7, 27, 20, 13,  2,
						  41, 52, 31, 37, 47, 55,
						  30, 40, 51, 45, 33, 48,
						  44, 49, 39, 56, 34, 53,
						  46, 42, 50, 36, 29, 32 };//PC_2置换表
	//feistel轮函数参数
	const int E[48]= { 32,  1,  2,  3,  4,  5,
						4,  5,  6,  7,  8,  9,
						8,  9, 10, 11, 12, 13,
					   12, 13, 14, 15, 16, 17,
					   16, 17, 18, 19, 20, 21,
					   20, 21, 22, 23, 24, 25,
					   24, 25, 26, 27, 28, 29,
					   28, 29, 30, 31, 32,  1 };//拓展置换表
	const int P[32] = { 16,  7, 20, 21,
					   29, 12, 28, 17,
						1, 15, 23, 26,
						5, 18, 31, 10,
						2,  8, 24, 14,
					   32, 27,  3,  9,
					   19, 13, 30,  6,
					   22, 11,  4, 25 };//P置换表
	const int S_BOX[8][4][16] = {
	{
		{14,4,13,1,2,15,11,8,3,10,6,12,5,9,0,7},
		{0,15,7,4,14,2,13,1,10,6,12,11,9,5,3,8},
		{4,1,14,8,13,6,2,11,15,12,9,7,3,10,5,0},
		{15,12,8,2,4,9,1,7,5,11,3,14,10,0,6,13}
	},
	{
		{15,1,8,14,6,11,3,4,9,7,2,13,12,0,5,10},
		{3,13,4,7,15,2,8,14,12,0,1,10,6,9,11,5},
		{0,14,7,11,10,4,13,1,5,8,12,6,9,3,2,15},
		{13,8,10,1,3,15,4,2,11,6,7,12,0,5,14,9}
	},
	{
		{10,0,9,14,6,3,15,5,1,13,12,7,11,4,2,8},
		{13,7,0,9,3,4,6,10,2,8,5,14,12,11,15,1},
		{13,6,4,9,8,15,3,0,11,1,2,12,5,10,14,7},
		{1,10,13,0,6,9,8,7,4,15,14,3,11,5,2,12}
	},
	{
		{7,13,14,3,0,6,9,10,1,2,8,5,11,12,4,15},
		{13,8,11,5,6,15,0,3,4,7,2,12,1,10,14,9},
		{10,6,9,0,12,11,7,13,15,1,3,14,5,2,8,4},
		{3,15,0,6,10,1,13,8,9,4,5,11,12,7,2,14}
	},
	{
		{2,12,4,1,7,10,11,6,8,5,3,15,13,0,14,9},
		{14,11,2,12,4,7,13,1,5,0,15,10,3,9,8,6},
		{4,2,1,11,10,13,7,8,15,9,12,5,6,3,0,14},
		{11,8,12,7,1,14,2,13,6,15,0,9,10,4,5,3}
	},
	{
		{12,1,10,15,9,2,6,8,0,13,3,4,14,7,5,11},
		{10,15,4,2,7,12,9,5,6,1,13,14,0,11,3,8},
		{9,14,15,5,2,8,12,3,7,0,4,10,1,13,11,6},
		{4,3,2,12,9,5,15,10,11,14,1,7,6,0,8,13}
	},
	{
		{4,11,2,14,15,0,8,13,3,12,9,7,5,10,6,1},
		{13,0,11,7,4,9,1,10,14,3,5,12,2,15,8,6},
		{1,4,11,13,12,3,7,14,10,15,6,8,0,5,9,2},
		{6,11,13,8,1,4,10,7,9,5,0,15,14,2,3,12}
	},
	{
		{13,2,8,4,6,15,11,1,10,9,3,14,5,0,12,7},
		{1,15,13,8,10,3,7,4,12,5,6,11,0,14,9,2},
		{7,11,4,1,9,12,14,2,0,6,10,13,15,3,5,8},
		{2,1,14,7,4,10,8,13,15,12,9,0,3,5,6,11}
	}
	};//SBOX

	const int ip_1[64] = { 40,8,48,16,56,24,64,32,
							  39,7,47,15,55,23,63,31,
							  38,6,46,14,54,22,62,30,
							  37,5,45,13,53,21,61,29,
							  36,4,44,12,52,20,60,28,
							  35,3,43,11,51,19,59,27,
							  34,2,42,10,50,18,58,26,
							  33,1,41, 9,49,17,57,25 };
	//初始置换
	bitset<64> IP(const bitset<64> plain)
	{
		bitset<64> IPS;
		for (int i = 0; i < 64; i++)
		{
			IPS[i] = plain[ip[i]-1];
		}
		return IPS;
	}
	//IP逆置换
	bitset<64> IP_1(const bitset<64>& S)
	{
		bitset<64> cipher;
		//构造ip逆置换
		for (int i = 0; i < 64; i++)
		{
			cipher[i] = S[ip_1[i] - 1];
		}
		return cipher;
	}
	bitset<32> F(const bitset<32>& r, const bitset<48>& subkey);//轮函数
	void gernerateSubkey(const bitset<64>& key);//生成子密钥

	//DES();
	bitset<64> encrypt(const bitset<64>& plain, const bitset<64>& key);
	bitset<64> decrypt(const bitset<64>& plain, const bitset<64>& key);
};
bitset<32> DES:: F(const bitset<32>& r, const bitset<48>& subkey) {
	//扩展
	bitset<48> Exp;
	bitset<32> Fout;
	//cout << "Exp:";
	for (int i = 0; i < 48; i++)
	{
		Exp[i] = r[E[i] - 1];
		//cout << Exp[i];
	}
	//cout << endl;
	//与子密钥异或
	/*cout << "org Exp";
	for (int i = 0; i < 48; i++)
		cout << Exp[i];
	cout << endl;*/
	Exp = Exp ^ subkey;
	/*cout << "Exp";
	for (int i = 0; i < 48; i++)
		cout << Exp[i];
	cout << endl;*/
	//分组，经过S盒置换
	for (int i = 0; i < 8; i++)
	{
		int head = i*6;//每一组第一位的下标
		int row = Exp[head] * 2 + Exp[head + 5];
		int col = Exp[head+1] * 8 + Exp[head+2] * 4 + Exp[head+3] * 2 + Exp[head+4];
		//cout << "row" << row << "col " << col << endl;
		//置换
		for (int j = 0; j < 4; j++)
		{
			Fout[i * 4 + j] = (S_BOX[i][row][col] >> (3-j)) & 1;
		}
	}
	/*cout << "S:";
	for (int i = 0; i < 32; i++)
		cout << Fout[i];
	cout << endl;*/
	//P置换
	bitset<32> tmp = Fout;
	//cout << "P:";
	for (int i = 0; i < 32; i++)
	{
		Fout[i] = tmp[P[i] - 1];
		//cout << Fout[i];
	}
	//cout << endl;
	return Fout;
}
void DES::gernerateSubkey(const bitset<64>& key) {
	bitset<56> cur;
	bitset<28> left;
	bitset<28> right;

	//pc_1置换
	for (int i = 0; i < 56; i++)
	{
		cur[i] = key[PC_1[i]-1];
		//cout << cur[i];
	}
	//cout << endl;
	for (int i = 0; i < 28; i++)
	{
		left[i] = cur[i];
	}
	for (int i = 0; i < 28; i++)
		right[i] = cur[i+28];

	//循环左移位+压缩置换
	int shiftBits[] = { 1, 1, 2, 2, 2, 2, 2, 2, 1, 2, 2, 2, 2, 2, 2, 1 };
	for (int round = 0; round < 16; round++)
	{
		leftShift(left, shiftBits[round]);
		leftShift(right, shiftBits[round]);
		//cout << "left" << round << ':';
		/*for (int j = 0; j < 28; j++)
			cout << left[j];
		cout << endl;
		cout << "right" << round << ':';
		for (int j = 0; j < 28; j++)
			cout << right[j];*/
		//合并
		for (int i = 0; i < 56; i++)
		{
			if (i < 28)
				cur[i] = left[i];
			else
				cur[i] = right[i-28];
		}

		//压缩置换
		//cout << "第i轮的密钥为:";
		for (int j = 0; j < 48; j++)
		{
			subKeys[round][j] = cur[PC_2[j]-1];
			//cout<< subKeys[round][j];
		}
		//cout << endl;
	}
}
bitset<64> DES:: encrypt(const bitset<64>& plain, const bitset<64>& key) {
	bitset<32> left;
	bitset<32> right;
	bitset<32> nextLeft;
	bitset<64> cur;

	cur = IP(plain);
	for (int i = 0; i < 32; i++)
	{
		left[i] = cur[i];
	}
	for (int i = 0; i < 32; i++)
	{
		right[i] = cur[i+32];
	}

	//16轮迭代
	gernerateSubkey(key);
	/*for (int i = 0; i < 16; i++)
	{
		cout << "第" << i << "轮的密钥为:" << endl;
		for (int j = 0; j < 48; j++)
			cout << subKeys[i][j];
		cout << endl;
	}*/
	for (int i = 0; i < 16; i++)
	{
		nextLeft = right;
		right = left ^ F(right, subKeys[i]);//异或
		/*cout << "f:";
		for (int i = 0; i < 32; i++)
			cout << right[i];
		cout << endl;*/
		left = nextLeft;
	}

	for (int i = 0; i < 32; i++)
		cur[i] = right[i];
	for (int i = 0; i < 32; i++)
		cur[i + 32] = left[i];
	return IP_1(cur);
}
// 解密
bitset<64> DES::decrypt(const bitset<64>& plain, const bitset<64>& key) {

	bitset<32> left; // 记录上半部分
	bitset<32> right; // 记录下半部分
	bitset<32> nextLeft; // 作为16轮迭代的中间临时变量
	bitset<64> cur; // 记录每一步置换的结果

	// 第一步：IP初始置换
	cur = IP(plain);

	// 获取L和R
	for (int i = 0; i < 32; i++)
		left[i] = cur[i];
	for (int i = 0; i < 32; i++)
		right[i] = cur[i+32];

	// 第二步：16轮迭代T
	gernerateSubkey(key);//生成子密钥
	for (int i = 0; i < 16; i++) {
		nextLeft = right;
		right = left ^ F(right, subKeys[15 - i]); // 子密钥调度顺序与加密时相反
		left = nextLeft;
	}

	// 第三步：交换置换
	for (int i = 0; i < 32; i++)
		cur[i] = right[i];
	for (int i = 0; i < 32; i++)
		cur[i + 32] = left[i];

	// 第四步：IP_1逆置换
	return IP_1(cur);
}


