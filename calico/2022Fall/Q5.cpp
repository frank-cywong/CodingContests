#include <iostream>
#include <climits>
#include <vector>

using namespace std;

typedef long long ll;

int B[100001];
int W[200001]; // sliding window of D days ending at day i
bool set[200001];

//ll DP[51][51]; // a[k][i] k cards used, last card used on day i

void doCase(){
	int N, K, D;
	cin >> N >> K >> D;
	vector<vector<ll>> DP;
	for(int i = 0; i <= K; ++i){
		vector<ll> temp;
		for(int j = 0; j < N; ++j){
			temp.push_back(0);
		}
		DP.push_back(temp);
	}
	int temp;
	for(int i = 0; i < N; ++i){
		cin >> temp;
		B[i] = temp;
	}
	ll sum = 0;
	int days = 0;
	for(int i = 0; i < (N + D); ++i){
		set[i] = false;
	}
	for(int i = 0; i < (N + D); ++i){
		if(i < N && B[i] == 0){
			for(int j = 0; j < D; ++j){
				if(days >= D){
					sum -= B[i+j-D];
				}
				days++;
				if(!set[i+j]){
					W[i+j] = sum;
				}
				set[i+j] = true;
			}
			days = 0;
			sum = 0;
		} else {
			if(days >= D){
				sum -= B[i-D];
				days--;
			}
			if(i < N){
				sum += B[i];
			}
			if(!set[i]){
				W[i] = sum;
			}
			days++;
		}
	}
/*
	ll max = 0;
	for(int i = 0; i < (N + D); ++i){
		if(W[i] > max){
			max = W[i];
		}
	}
*/
/*
	for(int i = 0; i < N; ++i){
		cout << "W[i+D-1] for i = " << i << " is: " << W[i+D-1] << endl;
	}
*/
	for(int k = 0; k <= K; ++k){
		for(int i = 0; i < N; ++i){
			if(k == 0){
				DP[k][i] = 0;
			} else {
				// case 1: no use card, copy from prev i
				ll cMax = 0;
				if(i > 0){
					cMax = DP[k][i-1];
				}
				// case 2: use card
				ll comp = 0;
				if(i >= D){
					comp = DP[k-1][i-D];
					//cout << "test\n";
				}
				comp += W[i+D-1];
				if(comp > cMax){
					cMax = comp;
				}
				//cout << "setting DP[" << k << "][" << i << "] to: " << cMax << endl;
				//cout << "comp: " << comp << ", cmax: " << cMax << endl;
				DP[k][i] = cMax;
			}
		}
	}
	ll max = 0;
	for(int k = 0; k <= K; ++k){
		if(DP[k][N-1] > max){
			max = DP[k][N-1];
		}
	}
	cout << max << endl;
}

int main(){
	int T;
	cin >> T;
	for(int i = 0; i < T; ++i){
		doCase();
	}
	return 0;
}
