#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>
#include <cmath>
#include <cstdio>
#include <cstring>

#define DEBUG 0

using namespace std;

vector<int> modflips;
int modflipcutoff = 2000; // sqrt(4000000)

char parity[4000001]; // buttons pressed, 1 or 0

void doCase(int t){
	int N;
	cin >> N;
	char p;
	int x;
	modflips.clear();
	memset(parity, 0, N+1);
	for(int i = 1; i <= N; ++i){
		cin >> p;
		x = (int)(p);
#if DEBUG
		cout << "X1: " << x << endl;
#endif
		for(auto it = modflips.begin(); it != modflips.end(); ++it){
			int d = *it;
			if(i % d == 0){
				++x; // flip parity
			}
		}
#if DEBUG
		cout << "X2: " << x << endl;
#endif
		x += parity[i]; // add any existing button changes
#if DEBUG
		cout << "X3: " << x << "i: " << i << endl;
#endif
		x %= 2; // parity reduce
		if(x == 1){
			parity[i] = 1; // PUSH THE BUTTON
			if(i <= modflipcutoff){
				modflips.push_back(i);
			} else {
				for(int k = 2 * i; k <= N; k += i){
					if(parity[k] == 1){
						--parity[k];
					} else {
						++parity[k];
					}
				}
			}
		} else {
			parity[i] = 0;
		}
	}
#if DEBUG
	for(int i = 1; i <= N; ++i){
		cout << (int)(parity[i]) << endl;
	}
#endif
	long long tcount = 0;
	long long tcount_s = 0;
	for(int i = 1; i <= N; ++i){
		if(parity[i] % 2){
			++tcount;
		}
	}
	int Q;
	cin >> Q;
	for(int i = 0; i < Q; ++i){
		int Qx;
		cin >> Qx;
		if(parity[Qx] == 1){
			--parity[Qx];
			--tcount;
		} else {
			++parity[Qx];
			++tcount;
		}
		tcount_s += tcount;
	}
	cout << "Case #" << t << ": " << tcount_s << endl;
}

int main(){
	cout << setprecision(32);
	int T;
	cin >> T;
	for(int i = 1; i <= T; i++){
		doCase(i);
	}
	return 0;
}