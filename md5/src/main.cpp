#include <iostream>
#include "MD5.h"
#include<sstream>
#include <iterator>
#include<ctype.h>
#include<string.h>
#include"test.h"
#include "tools.h"
int main(int argc, char* argv[]) {


	char test;
	printf("是否继续测试，如果是，请输入C ,否则请输入Q :\n");
	scanf("%c", &test);
	if (test == 'C')
	{
		for (int i = 0; i < 15; i++)
		{
			if (i == 7)
			{
				cout << "-----------------SNOW TEST---------------------" << endl;
			}
			cout << "TEST" << i + 1 << " " << endl;
			char* message = tests[i].msg;
			cout << "MESSAGE IS:  " << message << endl;
			char buffer[100];
			memset(buffer, 0, sizeof(buffer));
			sprintf(buffer, "%02X%02X%02X%02X%02X%02X%02X%02X%02X%02X%02X%02X%02X%02X%02X%02X",
				tests[i].hash[0], tests[i].hash[1], tests[i].hash[2], tests[i].hash[3],
				tests[i].hash[4], tests[i].hash[5], tests[i].hash[6], tests[i].hash[7],
				tests[i].hash[8], tests[i].hash[9], tests[i].hash[10], tests[i].hash[11],
				tests[i].hash[12], tests[i].hash[13], tests[i].hash[14], tests[i].hash[15]);
			for (int i = 0; i < strlen(buffer); i++)
			{
				buffer[i] = tolower(buffer[i]);
			}
			MD5 md;
			string result;
			result = md.pad(message);
			cout << "MD5 result：" << result << endl;
			string b;
			b = buffer;

			if (b == result)
			{
				cout << "true";
			}
			else
			{
				cout << "flase" << endl;
				string finala = htob(b);
				string finalb = htob(result);
				cout << "hex:" << finala << endl;
				cout << "hex:" << finalb << endl;
				int count = 0;
				for (int i = 0; i < 128; i++)
				{
					if (finala[i] != finalb[i])
						count++;
				}
				cout << "改变位数:" << count << endl;
			}

			cout << endl;
		}
	}


	system("pause");
	return 0;
}
