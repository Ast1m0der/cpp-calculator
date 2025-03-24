#include<iostream>;
#include<string>;
#include <windows.h>;
#include <cctype>;

using namespace std;

int calculate(string str) {
	char c;
	int res = 0;
	string num_str;
	bool first = true, finish, digit = false, sign = false;
	for (int i = 0; i < str.length(); i++) {
		char symb = str[i];
		if (isdigit(symb)) {
			num_str += symb;
			
			if (isdigit(str[(i + 1)])) {
				finish = false;
			}
			else {
				finish = true;
			}
			digit = true;
		}
		if (symb == '-' && (first || sign)) {
			num_str += symb;
		}

		if (digit && finish && first) {
			res = stoi(num_str);
			first = false;
			digit = false;
			num_str = "";
			finish = false;
		}
		if ((symb == '+' || symb == '-' || symb == '*' || symb == '/') && !sign) {
			c = symb;
			sign = true;
		}
		if (digit && finish) {
			switch (c)
			{
			case '-':
				res -= stoi(num_str);
				num_str = "";
				digit = false;
				sign = false;
				break;
			case '+':
				res += stoi(num_str);
				num_str = "";
				digit = false;
				sign = false;
				break;
			case '*':
				res *= stoi(num_str);
				num_str = "";
				digit = false;
				sign = false;
				break;
			case '/':
				res /= stoi(num_str);
				num_str = "";
				digit = false;
				sign = false;
				break;
			default:
				break;
			}
		}
	}
	return res;
}

int main() {
	SetConsoleOutputCP(65001);
	SetConsoleCP(1251);
	setlocale(LC_ALL, "RU");
	string str;
	cout << "Введите выражение: ";
	getline(cin, str);
	bool finish = false;
	int res_p;
	while (!finish) {
		int br[2];bool is_br = false;
		for (int i = 0; i < str.length(); i++) {
			char symb = str[i];
			if (symb == '(') {
				br[0] = i;
			}
			else if (symb == ')') {
				br[1] = i;
				is_br = true;
				break;
			}
			if ((i + 1) == str.length()) {
				finish = true;
			}
		}
		if (is_br) {
			res_p = calculate(str.substr(br[0], (br[1] - br[0] + 1)));
			str.replace(br[0], (br[1] - br[0] + 1), to_string(res_p));
		}
	}
	cout << "Ответ: " << calculate(str) << endl;
}