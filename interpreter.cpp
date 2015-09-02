#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <map>
#include "library.h"
using namespace std;

ifstream fin;
map<string, int>var;

vector < vector < string > > code;
vector < vector < short > > type;
//1-int
//2-string
//3-operator
void parse(){
	string s;
	int j = 0;
	while (getline(fin, s)){
		code.push_back(vector<string>());
		type.push_back(vector<short>());
		for (int i = 0; i < (int)s.length(); i++){
			string add;
			if (s[i] >= 'a' && s[i] <= 'z' || s[i] >= 'A' && s[i] <= 'Z'){
				while (s[i] >= 'a' && s[i] <= 'z' || s[i] >= 'A' && s[i] <= 'Z' && i<s.length())
					add += s[i], i++;
				code[j].push_back(add);
				type[j].push_back(2);
			}
			add = "";
			if (s[i] >= '0' && s[i] <= '9'){
				while (s[i] >= '0' && s[i] <= '9' && i < s.length())
					add += s[i], i++;
				code[j].push_back(add);
				type[j].push_back(1);
			}
			add = "";
			if (s[i] == '='){
				while (s[i] == '=' && i < s.length())
					add += s[i], i++;
				code[j].push_back(add);
				type[j].push_back(3);
			}
			add = s[i];
			if (s[i] == '+')
				code[j].push_back(add), type[j].push_back(3);
			if (s[i] == '-')
				code[j].push_back(add), type[j].push_back(3);
			if (s[i] == '*')
				code[j].push_back(add), type[j].push_back(3);
			if (s[i] == '/')
				code[j].push_back(add), type[j].push_back(3);
		}
		j++;
	}
}
int calc(int line, int from){
	char oper = '+';
	int ans = 0;
	for (int i = from; i < code[line].size(); i++){
		if (type[line][i] == 3)
			oper = code[line][i][0];
		else
		if (type[line][i] == 2)
			ans = obr(ans, var[code[line][i]], oper);
		else
			ans = obr(ans, ToInt(code[line][i]), oper);
	}
	return ans;
}
void print(int line){
	cout << calc(line, 1);
}
void println(int line){
	cout << calc(line, 1) << endl;
}
void read(int line){
	for (int i = 1; i < code[line].size(); i++){
		if (code[line][i] == "for" || code[line][i] == "if")
			error(2, line);
		cin >> var[code[line][i]];
	}
}
void doit(int line){
	if (code[line][0] == "read")
		read(line);
	if (code[line][0] == "print")
		print(line);
	if (code[line][0] == "println")
		println(line);
	if (type[line][1] == 3)
		var[code[line][0]] = calc(line, 2);
}
void interpret2(){
	for (int i = 0; i<code.size(); i++){
		if (code[i][0] != "for" && code[i][0] != "if"){
			doit(i);
		}
	}
}
int main(int argc, char* argv[]){
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	if (argc > 1){
		fin = ifstream(argv[argc - 1]);
		parse();
		interpret2();
	}
	else{
		fin = ifstream("ppp.myl");
		parse();
		interpret2();
		//interpret();
	}
	return 0;
}