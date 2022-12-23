#include<iostream>
#include<string>
#include<vector>
#include"key.h"
using namespace std;
string encode(string message) {
	string em = "";
	for (int i = 0; i < message.length(); i++)
	{
		int m, c;
		if (message[i] >= 'a' && message[i] <= 'z')
		{
			m = message[i] - 'a';
			c = (m + key) % 26;
			em += char('a' + c);
		}
		else if (message[i] >= 'A' && message[i] <= 'Z')
		{
			m = message[i] - 'A';
			c = (m + key) % 26;
			em += char('A' + c);
		}
		else
			em += message[i];
	}
	return em;
};
string decode(string em) {
	string m = "";
	for (int i = 0; i < em.length(); i++)
	{
		int c;
		if (em[i] >= 'a' && em[i] <= 'z')
		{
			c = em[i] - 'a';
			c = (c - key + 26) % 26;
			m += char('a' + c);
		}
		else if (em[i] >= 'A' && em[i] <= 'Z')
		{
			c = em[i] - 'A';
			c = (c - key + 26) % 26;
			m += char('A' + c);
		}
		else
			m += em[i];
	}
	return m;
};
int main() {
	string message;
	cout << "��������ܵ���Ϣ:\n";
	getline(cin, message);
	cout << "���ܽ��Ϊ:\n";
	string em = encode(message);
	cout << em << endl;
	cout << "���ܽ��Ϊ:\n";
	cout << decode(em) << endl;
	return 0;
}