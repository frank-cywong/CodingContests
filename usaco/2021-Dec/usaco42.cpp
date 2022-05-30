#include <iostream>

using namespace std;

int N;
int p[200001];

int check(int x) {
	int lbound = 0;
	int ubound = N;
	int c = 0;
	bool last = false; // true = HI, false = LO
	int temp;
	for (int i = 0; i < N; i++) {
		temp = p[i];
		if (temp < lbound || temp > ubound) {
			continue;
		}
		if (temp > x) {
			last = true;
			ubound = temp;
			continue;
		}
		if (last) {
			c++;
		}
		last = false;
		lbound = temp;
	}
	return c;
}

int main(){
	cin >> N;
	int temp;
	for (int i = 0; i < N; i++) {
		cin >> temp;
		p[i] = temp;
	}
	for (int i = 0; i <= N; i++) {
		cout << check(i) << endl;
	}
}
