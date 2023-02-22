#ifndef __TOOLS_H__
#define __TOOLS_H__
#include <string>
using namespace std;
string htob(string b)
{
	string result;
	for (int i = 0; i < 32; i++)
	{
		//cout << i << endl;
		if (b[i] == '0')
		{
			result += "0000";
		}
		if (b[i] == '1')
		{
			result += "0001";
		}
		if (b[i] == '2')
		{
			result += "0010";
		}
		if (b[i] == '3')
		{
			result += "0011";
		}
		if (b[i] == '4')
		{
			result += "0100";
		}
		if (b[i] == '5')
		{
			result += "0101";
		}
		if (b[i] == '6')
		{
			result += "0110";
		}
		if (b[i] == '7')
		{
			result += "0111";
		}
		if (b[i] == '8')
		{
			result += "1000";
		}
		if (b[i] == '9')
		{
			result += "1001";
		}
		if (b[i] == 'a')
		{
			result += "1010";
		}
		if (b[i] == 'b')
		{
			result += "1011";
		}
		if (b[i] == 'c')
		{
			result += "1100";
		}
		if (b[i] == 'd')
		{
			result += "1101";
		}
		if (b[i] == 'e')
		{
			result += "1110";
		}
		if (b[i] == 'f')
		{
			result += "1111";
		}//cout << finala[i] ;
	}

	return result;
}
#endif // !__TOOLS_H__

