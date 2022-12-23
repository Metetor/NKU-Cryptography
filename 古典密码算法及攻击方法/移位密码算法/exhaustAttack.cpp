#include<iostream>
#include<string>
using namespace std;
int main() {
	int guesskey=1;
	string dm;
	cout << "请输入要破译的密文:\n";	
	getline(cin, dm);
	for (; guesskey <= 25; guesskey++)
	{
		cout << "key:" << guesskey<<" ";
		for (int i = 0; i < dm.length(); i++)
		{
			int c;
			if (dm[i] >= 'a' && dm[i] <= 'z')
			{
				c = dm[i]-'a';
				cout << char('a' + (c - guesskey+26) % 26);
			}
			else if (dm[i] >= 'A' && dm[i] <= 'Z')
			{
				c=dm[i]-'A';
				cout << char('A' + (c - guesskey+26) % 26);
			}
			else
				cout << dm[i];
		}
		cout << endl;
	}
	return 0;
}