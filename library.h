#include <Windows.h>
#include <string>
using namespace std;
int ToInt(string s){
	int ans = 0;
	for (int i = 0; i < s.length(); i++)
		ans *= 10, ans += s[i] - '0';
	return ans;
}
void error(int x, int line = 0){
	if (x == 0){
		cout << "ERROR\n";
		cout << "division by zero\n";
	}
	if (x == 1){
		cout << "ERROR\n";
		cout << "trouble in a cycle\n";
	}
	if (x == 2){
		cout << "ERROR\nStrange name on line " << line << '\n';
	}
	system("pause");
	exit(0);
}
int obr(int now, int x, char oper){
	if (oper == '+')
		now += x;
	if (oper == '-')
		now -= x;
	if (oper == '*')
		now *= x;
	if (x == 0 && oper == '/'){
		error(0);
	}
	if (oper == '/')
		now /= x;
	return now;
}