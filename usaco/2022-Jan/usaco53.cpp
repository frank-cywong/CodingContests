#include <iostream>
#include <cstdlib>

#define debug 1

using namespace std;

int N;
int j[100000];
long long curlbound[100001];
long long curubound[100001];

long long K = 1000000000000LL;
long long diffinc = 1000000LL;

long long output[100001];

int main() {
#if debug == 1
	N = 50;
#else
	cin >> N;
#endif
	int temp;
	long long prev = 0LL;
	long long cur;
	for (int i = 0; i < N; i++) {
#if debug == 0
		cin >> temp;
		j[i] = temp;
#else
		if (i == 0) {
			j[i] = (rand() % 3) + 1;
		}
		else {
			j[i] = min(max(j[i - 1], i + 1) + (rand() % 4), N);
		}
#endif
		curlbound[i] = 1LL;
		curubound[i] = 1000000000000000000LL;
	}
	cout << K << endl;
	for (int i = 0; i < N; i++) {
		cur = curlbound[i];
#if debug == 1
		//cout << "cur set to curlbound for i = " << i << ", and curlbound = " << cur << endl;
#endif
		if (cur <= prev) {
			cur = prev + 1;
#if debug == 1
			//cout << "Adjusted cur to prev + 1 for i = " << i << endl;
#endif
		}
		if (i != 0 && j[i] != j[i - 1] && cur < (prev + diffinc)) {
			cur = prev + diffinc;
#if debug == 1
			//cout << "Adjusted cur to prev + diffinc for i = " << i << endl;
#endif
		}
		if (cur >= curubound[i]) {
			cur = curubound[i];
#if debug == 1
			//cout << "Adjusted cur to upper bound for i = " << i << endl;
#endif
		}
		cout << cur << endl;
#if debug == 1
		output[i] = cur;
#endif
		for (int k = -1; k < 10; k++) {
			curlbound[j[i] + k] = max(curlbound[j[i] + k], cur + 1 + K);
		}
		for (int k = i + 1; k < j[i]; k++) {
			curubound[k] = min(cur + 1 + K - (100 * (j[i] - k)), curubound[k]);
#if debug == 1
			//cout << "curubound[" << k << "] set to " << curubound[k] << " by i = " << i << endl;
#endif
		}
		prev = cur;
	}
#if debug == 1
	for (int k = 0; k < N; k++) {
		cout << j[k] << " ";
	}
	cout << endl;
	for (int k = 0; k < N; k++) {
		cout << curlbound[k] << " ";
	}
	cout << endl;
	for (int k = 0; k < N; k++) {
		cout << curubound[k] << " ";
	}
	cout << endl;
	for (int i = 0; i < N; i++) {
		if ((output[j[i] - 1] <= output[i] + K) && (output[j[i]] > output[i] + K || output[j[i]] == 0)) {
			cout << output[j[i] - 1] << " <= " << output[i] + K << " and " << output[j[i]] << " > " << output[i] + K << " for i = " << i << endl;
			continue;
		}
		cout << endl;
		cout << "ERROR" << endl;
		cout << "Check failed for i = " << i << " with output[j[i] - 1]: " << output[j[i] - 1] << ", output[i] + K: " << output[i] + K << ", output[j[i]]: " << output[j[i]] << endl;
		return 0;
	}
#endif
	return 0;
}