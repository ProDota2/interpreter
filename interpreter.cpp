#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <map>
using namespace std;
ifstream fin;
map<string, int>var;

void error(int x){
	if (x == 0){
		cout << "ERROR\n";
		cout << "division by zero\n";
	}
	if (x == 1){
		cout << "ERROR\n";
		cout << "trouble in a cycle\n";
	}
}
int obr(int now,int x,char oper){
	if (oper == '+')
		now += x;
	if (oper == '-')
		now -= x;
	if (oper == '*')
		now *= x;
	if (x == 0 && oper == '/'){
		error(0);
		system("pause");
		exit(0);
	}
	if (oper == '/')
		now /= x;
	return now;
}
int prs(string s, int x){
	int ans = 0;
	char oper = '+';
	for (int i = x; i<(int)s.length(); i++){
		int add = 0;
		string s_add = "";
		bool is_digit = true;
		if (s[i] >= '0' && s[i] <= '9'){
			while (s[i] >= '0' && s[i] <= '9' && i < (int)s.length())
				add *= 10, add += s[i] - '0', i++;
			ans = obr(ans, (is_digit ? add : var[s_add]), oper);
		}
		else if (s[i] >= 'a' && s[i] <= 'z' || s[i] >= 'A' && s[i] <= 'Z'){
			is_digit = false;
			while (s[i] >= 'a' && s[i] <= 'z' || s[i] >= 'A' && s[i] <= 'Z' && i < (int)s.length())
				s_add += s[i], i++;
			ans = obr(ans, (is_digit ? add : var[s_add]), oper);
		}
		if (s[i] == '+')
			oper = s[i];
		if (s[i] == '-')
			oper = s[i];
		if (s[i] == '*')
			oper = s[i];
		if (s[i] == '/')
			oper = s[i];
	}
	return ans;
}
void read(string s, int x){
	string name;
	for (int i = x; i < (int)s.length();i++)
	if (s[i] >= 'a' && s[i] <= 'z' || s[i] >= 'A' && s[i] <= 'Z'){
		while (s[i] >= 'a' && s[i] <= 'z' || s[i] >= 'A' && s[i] <= 'Z' && i < (int)s.length())
			name += s[i], i++;
	}
	cin >> var[name];
}
void cycle(string s, int x){
	int from = -1, to = -1;
	string id = "none";
	for (int i = x; i<(int)s.length(); i++){
		if (s[i] >= '0' && s[i] <= '9' && from == -1){
			from = 0;
			while (s[i] >= '0' && s[i] <= '9' && i<(int)s.length())
				from *= 10, from += s[i] - '0', i++;
		}
		if (s[i] >= '0' && s[i] <= '9' && to == -1){
			to = 0;
			while (s[i] >= '0' && s[i] <= '9' && i<(int)s.length())
				to *= 10, to += s[i] - '0', i++;
		}
		if (s[i] >= 'a' && s[i] <= 'z' || s[i] >= 'A' && s[i] <= 'Z'){
			id = "";
			while (s[i] >= 'a' && s[i] <= 'z' || s[i] >= 'A' && s[i] <= 'Z' && i < (int)s.length())
				id += s[i], i++;
		}
	}
	if (from == -1 || to == -1){
		error(1);
		return;
	}
	var[id] = from;
	string str;
	vector<string>cyc;
	while (getline(fin, str)){
		if (str == "##")
			break;
		cyc.push_back(str);
	}
	for (int t = from; t < to; t++){
		for (int j = 0; j < (int)cyc.size(); j++){
			string name;
			int ii;
			for (ii = 0; ii < (int)cyc[j].length(); ii++){
				if (cyc[j][ii] >= 'a' && cyc[j][ii] <= 'z' || cyc[j][ii] >= 'A' && cyc[j][ii] <= 'Z'){
					while (cyc[j][ii] >= 'a' && cyc[j][ii] <= 'z' || cyc[j][ii] >= 'A' && cyc[j][ii] <= 'Z' && ii < (int)cyc[j].length())
						name += cyc[j][ii], ii++;
					break;
				}
			}
			if (name == "print"){
				cout << prs(cyc[j], ii);
				continue;
			}
			if (name == "println"){
				cout << prs(cyc[j], ii) << endl;
				continue;
			}
			if (name == "read"){
				read(cyc[j],ii);
				continue;
			}
			var[name] = prs(cyc[j], ii);
		}
		var[id]++;
	}
}
void interpret(){
	string s;
	while (getline(fin, s)){
		string name;
		int i;
		for (i = 0; i < (int)s.length(); i++)
		if (s[i] >= 'a' && s[i] <= 'z' || s[i] >= 'A' && s[i] <= 'Z'){
			while (s[i] >= 'a' && s[i] <= 'z' || s[i] >= 'A' && s[i] <= 'Z' && i < (int)s.length())
				name += s[i], i++;
			break;
		}
		if (name == "print"){
			cout << prs(s, i);
			continue;
		}
		if (name == "println"){
			cout << prs(s, i) << endl;
			continue;
		}
		if (name == "for"){
			cycle(s, i);
			continue;
		}
		if (name == "read"){
			read(s, i);
			continue;
		}
		var[name] = prs(s, i);
	}
}
int main(int argc, char* argv[]){
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	if (argc > 1){
		fin = ifstream(argv[argc - 1]);
		interpret();
	}
	else{
		cout << "Sorry but it is not an .myl file";
	}
	return 0;
}