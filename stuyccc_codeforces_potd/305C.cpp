#include <iostream>

using namespace std;

typedef long long ll;

int main(){
	int n;
	cin >> n;
	ll curExp = 0;
	ll curCounter = 0;
	ll inp = 1;
	ll curExpCount = 0;
	ll nextA;
	cin >> nextA;
	bool init = true;
	while(inp < n || curExp < nextA || curExpCount != 0 || init){
		if(init){
			init = false;
		}
		while(nextA == curExp && inp < n){
			curExpCount++;
			cin >> nextA;
			inp++;
		}
		if(inp == n && nextA == curExp){
			curExpCount++;
		}
		//cout << "curExpCount: " << curExpCount << endl;
		//cout << "curExp: " << curExp << endl;
		if(curExpCount == 0){
			curCounter += (nextA - curExp);
			curExp = nextA;
		} else {
			if(curExpCount % 2 == 0){
				curCounter++;
			}
			curExpCount /= 2;
			curExp++;
		}
	}
	cout << curCounter << endl;
	return 0;
}
