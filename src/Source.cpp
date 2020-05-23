#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <deque>
#include <string>
#include <map>
#include <vector>
#include <fstream>
#include <ctime>

using namespace std;

typedef deque<string> prefix;          // ������� ���������
map<prefix, vector<string>> statetab; // �������-��������

const int NPREF = 5; // ���������� ���� � ��������
const int MAXGEN = 500; // ����� ������ �� ������

int main()
{
	srand(time(NULL)); // ����� ���������� ��������� �����
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	
	prefix pref;
	pref.push_back("START_OF_STATEMENT");
	string input_word = "";
	while (cin >> input_word) // ��������� ������� ������
	{
		input_word[0] = tolower(input_word[0]); // ���������� ���� � ������� ��������
		bool end_of_statement_flag = false;
		if (input_word[input_word.size() - 1] == '.' || input_word[input_word.size() - 1] == '!' || input_word[input_word.size() - 1] == '?')
		{ // �������� �� ����������� ����� �����������
			end_of_statement_flag = true;
			input_word = input_word.substr(0, input_word.size() - 1);
		}
		statetab[pref].push_back(input_word); // ���������� ��������
		pref.push_back(input_word);
		while (pref.size() > NPREF)
		{
			pref.pop_front();
		}
		if (end_of_statement_flag)
		{
			statetab[pref].push_back("END_OF_STATEMENT");
			pref.clear();
			pref.push_back("START_OF_STATEMENT");
		}
	}

	pref.clear();		// ��������� �������� ������ �����������
	pref.push_back("START_OF_STATEMENT");
	for (int i = 0; i < MAXGEN; i++)
	{
		if (statetab.find(pref) == statetab.end()) // ��������� ������ ������������ �������� ��� �������� ��������
		{
			break;
		}

		string word_to_add = statetab[pref][rand() % statetab[pref].size()]; // ����� ���������� ����� �� ������� �������-�������
		if (word_to_add == "END_OF_STATEMENT") // �������� ��������� �����������
		{
			cout << '.'; // ��������� �����������
			pref.clear();		// ��������� �������� ������ �����������
			pref.push_back("START_OF_STATEMENT");
			i--; // ����� ����� �� ���������, �������� �� �������������
			continue;
		}

		if (pref.size() == 1 && pref[0] == "START_OF_STATEMENT") // ������������� ������ ����� � �����������
		{
			word_to_add[0] = toupper(word_to_add[0]);
		}
		
		cout << ' ' << word_to_add; // ������ ������ ����� � �����������
		input_word[0] = tolower(input_word[0]); // ���������� ���� � ������� ��������

		pref.push_back(word_to_add); // ���������� ��������
		while (pref.size() > NPREF)
		{
			pref.pop_front();
		}
	}

	cout << ".\n"; // ���������� ��������� ������
}