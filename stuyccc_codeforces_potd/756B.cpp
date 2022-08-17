#include <iostream>
#include <queue>
#include <algorithm>

using namespace std;

int curOptimalCost[100001];
int main(){
	int n;
	cin >> n;
	queue<int> MIN90;
	queue<int> MIN1440;
	int tick = 0;
	curOptimalCost[0] = 0;
	for(int i = 0; i < n; i++){
		cin >> tick;
		MIN90.push(tick);
		MIN1440.push(tick);
		while(MIN90.front() <= tick - 90){
			MIN90.pop();
		}
		while(MIN1440.front() <= tick - 1440){
			MIN1440.pop();
		}
		int simplyPayCost = 20 + curOptimalCost[i];
		int pay90Cost = 50 + curOptimalCost[max(0, (int)(i - MIN90.size() + 1))];
		int pay1440Cost = 120 + curOptimalCost[max(0, (int)(i - MIN1440.size() + 1))];
		curOptimalCost[i+1] = min(min(simplyPayCost, pay90Cost), pay1440Cost);
		cout << curOptimalCost[i+1] - curOptimalCost[i] << endl;
	}
	return 0;
}
