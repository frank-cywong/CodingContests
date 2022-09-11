#include <iostream>
#include <cstring>

using namespace std;

void doCase(int t){
	int freqArr[101];
	memset(freqArr, 0, sizeof(int) * 101);
	int N, K;
	cin >> N >> K;
	int temp;
	bool failed = false;
	if(N > (2 * K)){
		failed = true;
	}
	for(int i = 0; i < N; i++){
		cin >> temp;
		if(failed){
			continue;
		}
		freqArr[temp]++;
		if(freqArr[temp] > 2){
			failed = true;
		}
	}
	cout << "Case #" << t << ": " << (failed ? "NO\n" : "YES\n");
	return;
}

int main(){
	int T;
	cin >> T;
	for(int i = 1; i <= T; i++){
		doCase(i);
	}
}
