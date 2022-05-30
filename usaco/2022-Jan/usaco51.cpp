#include <iostream>

using namespace std;

int N;

const int mod = 1000000007;

int dp[101][1001];

int h[100];

int doDP() {
	for (int i = 1; i < N; i++) {
		for (int j = 0; j <= h[i]; j++) {
			if (i == 1) {
				if (j <= h[0]) {
					dp[i][j] = j + 1;
				}
				else {
					dp[i][j] = h[0] + 1;
				}
				continue;
			}
			if (j == 0) {
				dp[i][j] = dp[i - 1][h[i - 1]];
				continue;
			}
			if (j <= h[i - 1]) {
				dp[i][j] = (dp[i][j - 1] + dp[i - 1][h[i - 1] - j]) % mod;
				continue;
			}
			dp[i][j] = dp[i][j - 1];
		}
	}
	return dp[N - 1][h[N - 1]];
}

int main() {
	cin >> N;
	int temp;
	for (int i = 0; i < N; i++) {
		cin >> temp;
		h[i] = temp;
	}
	if (N % 2 == 0) {
		cout << doDP();
		return 0;
	}
	int curminh = 1000;
	for (int i = 0; i < N; i++) {
		if (h[i] < curminh) {
			curminh = h[i];
		}
	}
	int output = 0;
	for (int dec = 0; dec <= curminh; dec++) {
		output += doDP();
		output %= mod;
		for (int i = 0; i < N; i++) {
			h[i]--;
		}
	}
	cout << output;
	return 0;
}