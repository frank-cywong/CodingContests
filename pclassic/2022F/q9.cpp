#include <iostream>
#include <vector>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <cstdlib>

using namespace std;

long long findSum(vector<int> arr, int k) {
	long long sum = 0;
	long long n = arr.size();
	for(int i = 1; i <= n; ++i){
		long long lt = n - i;
		long long rt = i - 1;
		long long m = (arr[i - 1] % k);
		long long lv = arr[i - 1] - m;
		lv *= lt;
		long long rv = m;
		rv *= rt;
		sum += lv;
		sum += rv;
	}
	return sum;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);

	int t;
	cin >> t;

	while (t--) {
		int n, k;
		cin >> n >> k;
		vector<int> arr;
		arr.resize(n);
		for (int i = 0; i < n; i++) {
			cin >> arr[i];
		}
		long long sum = findSum(arr, k);
		cout << sum << endl;
	}
	return 0;
}