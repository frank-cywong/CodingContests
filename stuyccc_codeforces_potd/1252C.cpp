#include <iostream>
#include <algorithm>

using namespace std;

int R[100001];
int Q[100001];
int RESum[100001];
int QESum[100001];

int main(){
	int N, Qc;
	cin >> N >> Qc;
	int temp;
	for(int i = 1; i <= N; i++){
		cin >> temp;
		R[i] = temp;
	}
	for(int i = 1; i <= N; i++){
		cin >> temp;
		Q[i] = temp;
	}
	RESum[0] = 0;
	QESum[0] = 0;
	for(int i = 1; i <= N; i++){
		if(R[i] % 2 == 0){
			RESum[i] = RESum[i-1] + 1;
		} else {
			RESum[i] = RESum[i-1];
		}
		if(Q[i] % 2 == 0){
			QESum[i] = QESum[i-1] + 1;
		} else {
			QESum[i] = QESum[i-1];
		}
	}
	int ra, ca, rb, cb;
	for(int i = 0; i < Qc; i++){
		cin >> ra >> ca >> rb >> cb;
		if(((R[ra] + Q[ca]) % 2 == 1) || ((R[rb] + Q[cb]) % 2 == 1)){
			cout << "NO\n";
			continue;
		}
		if(rb < ra){
			swap(ra, rb);
		}
		if(cb < ca){
			swap(ca, cb);
		}
		int rEc = RESum[rb] - RESum[ra - 1];
		int rTc = rb - ra + 1;
		if(rEc != rTc && rEc != 0){
			cout << "NO\n";
			continue;
		}
		int qEc = QESum[cb] - QESum[ca - 1];
		int qTc = cb - ca + 1;
		if(qEc != qTc && qEc != 0){
			cout << "NO\n";
			continue;
		}
		cout << "YES\n";
	}
	return 0;
}
