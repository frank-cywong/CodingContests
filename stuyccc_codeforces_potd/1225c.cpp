#include <iostream>
#include <climits>

using namespace std;

int main(){
	int n, p;
	cin >> n >> p;
	if(p == 0){
		cout << __builtin_popcount(n) << endl;
		return 0;
	}
	int curbest = INT_MAX;
	int curPCount = 0;
	int tempBCount;
	while(true){
		curPCount++;
		n -= p;
		if(n <= 0){
			break;
		}
		tempBCount = __builtin_popcount(n);
		if(tempBCount <= curPCount && n >= curPCount){ // if less than, still works provided n >= curPCount (you can't split up 2^0 beyond this, so best case is n * 2^0), just split up larger ones into smaller ones
			curbest = curPCount;
			break;
		}
	}
	if(curbest == INT_MAX){
		cout << -1 << endl;
	} else {
		cout << curbest << endl;
	}
	return 0;
}
