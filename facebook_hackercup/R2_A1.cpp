#include <iostream>
#include <string>
#include <cstring>

// NOT WORKING, RAN OUT OF TIME

using namespace std;

int prefixsum[100001][26];

int abs(int a){
	return (a < 0 ? a * -1 : a);
}

void doCase(int t){
	cout << "Case #" << t << ": ";
	string s;
	cin >> s;
	memset(prefixsum, 0, sizeof(prefixsum));
	int cur = 1;
	for(auto it = s.begin(); it != s.end(); it++){
		for(int i = 0; i < 26; i++){
			prefixsum[cur][i] = prefixsum[cur-1][i];
			if(i == (int)(*it - 'a')){
				prefixsum[cur][i]++;
			}
		}
		cur++;
	}
	int Q;
	cin >> Q;
	int sum = 0;
	int L, R;
	for(int q = 0; q < Q; q++){
		cin >> L >> R;
		if(L == R){
			sum++;
			continue;
		}
		if((R - L) % 2 == 0){
			int M = (L + R) / 2;
			int lsum1[26];
			int rsum1[26];
			bool usedoffset = false;
			bool failed = false;
			for(int i = 0; i < 26; i++){
				lsum1[i] = prefixsum[M][i] - prefixsum[L-1][i];
				rsum1[i] = prefixsum[R][i] - prefixsum[M][i];
				if(lsum1[i] == rsum1[i]){
					continue;
				}
				if(abs(rsum1[i] - lsum1[i]) > 1){
					failed = true;
					break;
				}
				if(usedoffset = true){
					failed = true;
					break;
				}
				usedoffset = true;
			}
			if(!failed && usedoffset){
				sum++;
				continue;
			}
			usedoffset = false;
			failed = false;
			for(int i = 0; i < 26; i++){
				lsum1[i] = prefixsum[M-1][i] - prefixsum[L-1][i];
				rsum1[i] = prefixsum[R][i] - prefixsum[M-1][i];
				if(lsum1[i] == rsum1[i]){
					continue;
				}
				if(abs(rsum1[i] - lsum1[i]) > 1){
					failed = true;
					break;
				}
				if(usedoffset = true){
					failed = true;
					break;
				}
				usedoffset = true;
			}
			if(!failed && usedoffset){
				sum++;
				continue;
			}
		}
	}
	cout << sum << endl;
}

int main(){
	int T;
	cin >> T;
	for(int i = 1; i <= T; i++){
		doCase(i);
	}
	return 0;
}
