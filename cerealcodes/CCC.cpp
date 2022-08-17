#include <iostream>

using namespace std;

long long sumUpToPrefixSum[100001];
long long notPalindromePrefixSum[100001];

int MOD = 1000000007;

int main(){
	sumUpToPrefixSum[0] = 0;
	for(int i = 1; i <= 100000; i++){
		long long temp = sumUpToPrefixSum[i - 1];
		temp *= 2;
		temp++;
		temp %= MOD;
		sumUpToPrefixSum[i] = temp;
	}
	notPalindromePrefixSum[0] = 0;
	for(int i = 1; i <= 100000; i++){
		long long tempPalindromeCount = sumUpToPrefixSum[i / 2] + 1;
		long long notPalindromeCount = (sumUpToPrefixSum[i] - sumUpToPrefixSum[i - 1] - tempPalindromeCount + MOD + MOD + MOD) % MOD;
		notPalindromePrefixSum[i] = notPalindromePrefixSum[i-1] + notPalindromeCount;
	}
	int t;
	cin >> t;
	for(int i = 0; i < t; i++){
		int l, r;
		cin >> l >> r;
		cout << (notPalindromePrefixSum[r] - notPalindromePrefixSum[l - 1] + MOD) % MOD << endl;
	}
	return 0;
}
