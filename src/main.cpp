#include <iostream>
#include <string>
#include <queue>
#include <map>
#include <fstream>
#include <time.h>
using namespace std;

typedef deque<string> prefix; // ������� ���������
const int NPREF = 2; // ���������� ���� � ��������
const int MAXGEN = 1000; // ����� ������ �� ������ 
const int out_str_len = 10;


int main() {
	setlocale(LC_ALL, "Russian");
	srand(time(NULL));
	ifstream fin;
	fin.open("input.txt");
	if (fin.is_open()) {
		prefix starting_prefix, current_prefix;
		map<prefix, vector<string> > statetab; // �������-��������
		string current_word;

		for (int i = 0; i < NPREF; i++) {
			fin >> current_word;
			current_prefix.push_back(current_word); // �������� ������ NPREF ���� 
		}
		starting_prefix = current_prefix;

		while (fin >> current_word) {
			statetab[current_prefix].push_back(current_word); // �������� � �������� w1 � w2 �������
			current_prefix.pop_front(); 
			current_prefix.push_back(current_word); // ������ w1 � w2 �� w2 � w3
		}
		fin.close();

		ofstream fout;
		fout.open("output.txt");

		for (auto str : starting_prefix) {
			fout << str << " "; // �������� ������ �������
		}
		current_prefix = starting_prefix; 		
		for (int i = NPREF; i < MAXGEN; i++) { // ������� � NPREF, ��� ��� �� ������ ��� ������ ��� ����� 
			if (statetab[current_prefix].empty()) break; // ���� � �������� ��� ���������, ����������� �����
			int suffix_ind = rand() % statetab[current_prefix].size(); // ��������� ������ ��������
			fout << statetab[current_prefix][suffix_ind] << " "; // �������� ��������� �������
			if (i % out_str_len == 0) {
				fout << endl; 
			}
			current_prefix.push_back(statetab[current_prefix][suffix_ind]); 
			current_prefix.pop_front();
		}		

		fout.close();
		return 0;
	}
	else {
		cout << "Error opening a file" << endl;
		return -1;
	}
}