/*
ID: Chun Yeung Wong [frankcw]
TASK: count_the_cows
LANG: C++11
*/

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cstring>
#include <set>
#include <queue>
#include <iterator>
#include <cstdlib>
#include <cmath>
#include <string>

using namespace std;

int Q;

long long tempx, tempy, tempd;

struct qdata {
	long long d;
	long long x;
	long long y;
};

vector<qdata> queries;

long long matchcountinrange(string in) {
	long long output = 0;
	for (int i = 0; i < in.size(); i++) {
		if (in[i] == '2') {
			output += (long long)2 ^ (in.size() - 1 - i);
		}
	}
	return output;
}

string long_to_ternary_string(long long v) {
	string output = "";
	string curchar = "";
	while (true) {
		curchar = to_string((v % 3));
		output += curchar;
		v /= 3;
		if (v == 0) {
			break;
		}
	}
	return output;
}

long long query(long long d, long long x, long long y) {
	if (x == y) {
		return (d + 1);
	}
	long long diff = llabs(y - x);
	if ((diff & 1) == 1) {
		return 0;
	}
	string diff_str = "";
	diff_str = long_to_ternary_string(diff);
	size_t exists_one = diff_str.find("1");
	if (exists_one != string::npos) {
		return 0;
	}
	long long temp;
	if (x > y) {
		temp = x;
		x = y;
		y = temp;
	} // x <= y
	vector<int> pos_zero;
	int string_len = diff_str.size();
	for (int i = 0; i < string_len; i++) {
		if (diff_str[i] == '0') {
			pos_zero.push_back(string_len - 1 - i);
		}
	}
	long long pow3 = (long long)3;
	long long xmoddiff = x % (pow3 ^ string_len);
	long long endxmoddiff = (x + d) % (pow3 ^ string_len);
	string xmoddiff_str = long_to_ternary_string(xmoddiff);
	string endmoddiff_str = long_to_ternary_string(endxmoddiff);
	long long mainpart = (pow3 ^ (pos_zero.size() - 1)) * (((x + d) / (pow3 ^ string_len)) - (x / (pow3 ^ string_len)));
	long long endpart = matchcountinrange(endmoddiff_str);
	long long startpart = matchcountinrange(xmoddiff_str);
	long long output = mainpart + endpart - startpart;
	return output;
}

int main() {
	cin >> Q;
	qdata temps;
	for (int i = 0; i < Q; i++) {
		cin >> tempd >> tempx >> tempy;
		temps.d = tempd;
		temps.x = tempx;
		temps.y = tempy;
		queries.push_back(temps);
	}
	for (vector<qdata>::iterator it = queries.begin(); it != queries.end(); it++) {
		cout << query((*it).d, (*it).x, (*it).y) << endl;
	}
	return 0;
}

