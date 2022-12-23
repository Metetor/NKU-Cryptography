#include<iostream>
#include<string>
#include<vector>
using namespace std;
string Table = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
char table[26] = "I like crypto very much";
string process() {

	string trans;
	for (int i = 0; i < strlen(table); i++)
	{//ת��Ϊ��д
		if (table[i] >= 'a' && table[i] <= 'z')
			table[i] = char(table[i] - 'a' + 'A');
	}
	for (int i = strlen(table)-1; i>=0 ; i--)
	{//������
		bool flag = false;
		if (table[i] < 'A' || table[i]>'Z')
			continue;
		for (int j = i - 1; j >= 0; j--)
		{
			if (table[i] == table[j])
				flag = true;
		}
		if (!flag)
			trans += table[i];
	}
	reverse(trans.begin(), trans.end());
	for (int i = 0; i < Table.length(); i++)
	{
		if (trans.find(Table[i]) != trans.npos)
		{
			continue;
		}
		else
			trans += Table[i];
	}
	return trans;
}
string encode(string message,string transTable) {
	string em;
	for (int i = 0; i < message.length(); i++)
	{
		if (message[i] >= 'a' && message[i] <= 'z')
			message[i] = char(message[i] - 'a' + 'A');
		else if (message[i] < 'A' || message[i]>'Z')
		{
			em += message[i];
			continue;
		}
		em += char(transTable[message[i] - 'A']);
	}
	return em;
}
string decode(string em, string transTable)
{
	string dm;
	for (int i = 0; i < em.length(); i++)
	{
		if (em[i] < 'A' || em[i]>'Z')
		{
			dm += em[i];
			continue;
		}
		dm += Table[transTable.find_first_of(em[i])];
	}
	return dm;
}
int main() {
	string message,em,dm;
	string transTable = process();
	cout << "����������m:\n";
	getline(cin, message);
	cout << "���ܺ������Ϊ:\n";
	em=encode(message, transTable);
	dm = decode(em, transTable);
	cout << em << endl;
	cout << "���ܺ������Ϊ:\n";
	cout << dm << endl;
	return 0;
}