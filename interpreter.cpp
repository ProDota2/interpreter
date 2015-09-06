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
			if (s[i] == '=' && s[i + 1] != '='){
				code[j].push_back("=");
				type[j].push_back(3);
				i += 1;
				continue;
			}
			if (s[i] == '=' && s[i + 1] == '='){
				code[j].push_back("==");
				type[j].push_back(3);
				i += 1;
				continue;
			}
			if (s[i] == '<' && s[i + 1] == '='){
				code[j].push_back("<=");
				type[j].push_back(3);
				i += 1;
				continue;
			}
			if (s[i] == '>' && s[i + 1] == '='){
				code[j].push_back(">=");
				type[j].push_back(3);
				i += 1;
				continue;
			}
			if (s[i] == '>' && s[i+1]!='='){
				code[j].push_back(">");
				type[j].push_back(3);
				//i++;
				continue;
			}
			if (s[i] == '<'&& s[i+1]!='='){
				code[j].push_back("<");
				type[j].push_back(3);
				i += 1;
				continue;
			}
			if (s[i] == '}'){
				code[j].push_back("}");
				type[j].push_back(3);
				//i++;
				continue;
			}
			if (s[i] == '{'){
				code[j].push_back("{");
				type[j].push_back(3);
				//i++;
				continue;
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
	string oper = "+";
	int ans = 0;
	for (int i = from; i < code[line].size(); i++){
		if (oper == ">" || oper == "<" || oper == ">=" || oper == "<=" || oper == "=="){
			return check(ans, calc(line, i), oper);
		}
		if (type[line][i] == 3)
			oper = code[line][i];
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
	if (code[line][0] == "{")
		return;
	if (code[line][0] == "}")
		return;
	if (code[line][0] == "read")
		read(line);
	if (code[line][0] == "print")
		print(line);
	if (code[line][0] == "println")
		println(line);
	if (type[line][1] == 3)
		var[code[line][0]] = calc(line, 2);
}
void interpret2(int from ,int to){
	for (int i = from; i < to; i++){
		if (code[i][0] != "for" && code[i][0] != "if"){
			doit(i);
		}
		if (code[i][0] == "if"){
			int c = 0;
			int tt = from;
			for (int j = i + 1; j < to; j++){
				if (code[j].size()>1 && code[j][0] == "{")
					c++;
				if (code[j].size()>1 && code[j][0] == "}")
					c--;
				if (c == 0){
					tt = j;
					break;
				}
			}
			if (calc(i, 1) == 1){
				interpret2(i+1, tt);
			}
			else{
				i = tt+1;
			}
		}
	}
}
int main(int argc, char* argv[]){
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	if (argc > 1){
		fin = ifstream(argv[argc - 1]);
		parse();
		interpret2(0, code.size());
	}
	else{
		fin = ifstream("ppp.myl");
		parse();
		interpret2(0, code.size());
		//interpret();
	}
	return 0;
}