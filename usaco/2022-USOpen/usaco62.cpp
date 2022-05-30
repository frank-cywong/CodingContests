#include <iostream>
#include <string>
#include <cstring>
#include <vector>

using namespace std;

int modval = 1000000007;

int dp[2001][2001]; // for any pos, let dp[a][b] represent the number of distinct values where only the instructions from [0,a) of a and [0,b) of b are considered

string sa, sb;

int get_val(int a, int b) {
	if (dp[a][b] != -1) {
		return dp[a][b];
	}
	// if either b or a are 0, return 1
	if (a == 0 || b == 0) {
		return 1;
	}
	// if any of the last chars are 0, then anything before it in that row can be assumed to not exist, ie return num of + in other line + 1
	if (sa[a - 1] == '0') {
		int returncount = 1;
		for (int sumplus = 0; sumplus < b; sumplus++) {
			dp[a][sumplus] = returncount;
			if (sb[sumplus] == '+') {
				returncount++;
			}
		}
		dp[a][b] = returncount;
		return dp[a][b];
	}
	if (sb[b - 1] == '0') {
		int returncount = 1;
		for (int sumplus = 0; sumplus < a; sumplus++) {
			dp[sumplus][b] = returncount;
			if (sa[sumplus] == '+') {
				returncount++;
			}
		}
		dp[a][b] = returncount;
		return dp[a][b];
	}
	// if any of the last chars are 1, then that char can be ignored
	if (sa[a - 1] == '1') {
		dp[a][b] = get_val(a - 1, b);
		return dp[a][b];
	}
	if (sb[b - 1] == '1') {
		dp[a][b] = get_val(a, b - 1);
		return dp[a][b];
	}
	// if char at a-1 or b-1 is +, decompose that first
	if (sa[a - 1] == '+') {
		// find previous number
		// if no prev numbers, return get_val(a-1, b)
		int prevconst = -1;
		for (int prevmulttest = b - 1; prevmulttest >= 0; prevmulttest--) {
			if (sb[prevmulttest] != '+' && sb[prevmulttest] != '1') { // also if its a 1, ignore
				prevconst = prevmulttest;
				break;
			}
		}
		if (prevconst == -1) {
			dp[a][b] = get_val(a-1, b);
			return dp[a][b];
		}
		// either + is placed before prevconst or after prevconst
		// if before, then only consider up to prevconst), if after, then ignore the +
		dp[a][b] = (get_val(a, prevconst) + get_val(a - 1, b)) % modval;
		return dp[a][b];
	}
	if (sb[b - 1] == '+') {
		// find previous number
		// if no prev numbers, return get_val(a, b-1)
		int prevconst = -1;
		for (int prevmulttest = a - 1; prevmulttest >= 0; prevmulttest--) {
			if (sa[prevmulttest] != '+' && sa[prevmulttest] != '1') {
				prevconst = prevmulttest;
				break;
			}
		}
		if (prevconst == -1) {
			dp[a][b] = get_val(a, b - 1);
			return dp[a][b];
		}
		// either + is placed before prevconst or after prevconst
		// if before, then only consider up to prevconst), if after, then ignore the +
		dp[a][b] = (get_val(prevconst, b) + get_val(a, b - 1)) % modval;
		return dp[a][b];
	}
	// otherwise, both end on multiplicative terms
	// find prev + on a
	// if no such + exists, then a is all multiplicative
	int prevplus = -1;
	for (int prevplustest = a - 1; prevplustest >= 0; prevplustest--) {
		if (sa[prevplustest] == '+') {
			prevplus = prevplustest;
			break;
		}
	}
	if (prevplus != -1) {
		// prevplus at a must either go before the last char of b (b-1), or after it
		// if before, then get_val(a, b-1), if after, then get_val(prevplus, b)
		dp[a][b] = (get_val(a, b - 1) + get_val(prevplus, b)) % modval;
		return dp[a][b];
	}
	// now test for b
	prevplus = -1;
	for (int prevplustest = b - 1; prevplustest >= 0; prevplustest--) {
		if (sb[prevplustest] == '+') {
			prevplus = prevplustest;
			break;
		}
	}
	if (prevplus != -1) {
		// prevplus at b must either go before the last char of a (a-1), or after it
		// if before, then get_val(a-1, b), if after, then get_val(a, prevplus)
		dp[a][b] = (get_val(a - 1, b) + get_val(a, prevplus)) % modval;
		return dp[a][b];
	}
	// if both multiplicative only, return 1
	return 1;
}

void do_test_case() {
	int N;
	cin >> N;
	cin >> sa >> sb;
	for (int i = 0; i < 2001; i++) {
		memset(dp[i], -1, sizeof(int) * 2001);
	}
	// preprocessing: remove all 1's and terms before 0's if they exist
	string nsa = "";
	string nsb = "";
	for (int i = N - 1; i >= 0; i--) {
		if (sa[i] == '0') {
			nsa = '0' + nsa;
			break;
		}
		if (sa[i] != '1') {
			nsa = sa[i] + nsa;
		}
	}
	for (int i = N - 1; i >= 0; i--) {
		if (sb[i] == '0') {
			nsb = '0' + nsb;
			break;
		}
		if (sb[i] != '1') {
			nsb = sb[i] + nsb;
		}
	}
	sa = nsa;
	sb = nsb;
	cout << get_val(nsa.size(), nsb.size()) << endl;
}

int main() {
	int T;
	cin >> T;
	for (int casenum = 0; casenum < T; casenum++) {
		do_test_case();
	}
	return 0;
}