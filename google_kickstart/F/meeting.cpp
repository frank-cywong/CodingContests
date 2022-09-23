#include <iostream>
#include <vector>
#include <climits>
#include <algorithm>
#include <cstring>

using namespace std;

#define DEBUG 0

struct meeting{
	int P;
	int L;
	int R;
};

int maxfunc(int a, int b){
	return(a >= b ? a : b);
}

int minfunc(int a, int b){
	return(a <= b ? a : b);
}
vector<meeting> meetings;
void doCase(int t){
	int N, K, X, D, M;
	cin >> N >> K >> X >> D >> M;
	/*
	int counter[101][101];
	for(int i = 0; i < 101; i++){
		for(int j = 0; j < 101; j++){
			counter[i][j] = 0;
		}
	}
	*/
	int counter[100000];
	meetings.clear();
	int tP, tL, tR;
	for(int i = 0; i < M; i++){
		cin >> tP >> tL >> tR;
		meeting tempM;
		tempM.P = tP - 1;
		tempM.L = tL - X + 1;
		tempM.R = tR;
		meetings.push_back(tempM);
/*
		for(int affectedTime = maxfunc(0, tL - X + 1); affectedTime < tR; affectedTime++){
			counter[affectedTime][tP-1]++;
		}
*/
	}
	int min = INT_MAX;
	for(int startTime = 0; startTime <= (D - X); startTime++){
		memset(counter, 0, sizeof(int) * N);
		for(auto it = meetings.begin(); it != meetings.end(); it++){
			if(startTime < it->R && startTime >= it->L){
				counter[(it->P)]++;
			}
		}
		nth_element(counter, counter + K - 1, counter + N);
#if DEBUG
		for(int i = 0; i < N; i++){
			cout << counter[i] << " ";
		}
		cout << endl;
#endif
		int req = 0;
		for(int i = 0; i <= K - 1; i++){
			req += counter[i];
		}
		if(req < min){
			min = req;
		}
	}
	cout << "Case #" << t << ": " << min << endl;
}

int main(){
	int T;
	cin >> T;
	for(int i = 1; i <= T; i++){
		doCase(i);
	}
	return 0;
}