#include <iostream>
#include <map>
#include <vector>
#include <set>

// NOT WORKING

#define DEBUG 0
#define PRINT_PROGRESS 1

using namespace std;

struct order{
	int bP;
	int sP;
	int bD;
	int sD;
};

vector<order> orders;
map<int, multimap<int, int>> buyorders;

multimap<int, int> processOrder;

multiset<long long> paths;

multiset<long long> pathArr[1000000];

vector<pair<int, int>> adjlist[1000000]; // pair (target, profit)

//long long pathEndAtSum[1000000];
//long long pathEndAtCnt[1000000];

#if PRINT_PROGRESS
int oT = 0;
int procCount = 0;
#endif

long long MOD = 1000000007;

void doCase(int t){
	int N, K;
	cin >> N >> K;
	orders.clear();
	orders.reserve(N);
	buyorders.clear();
	processOrder.clear();
	paths.clear();
	int A, B, X, Y;
	cout << "Case #" << t << ": ";
	for(int i = 0; i < N; i++){
		adjlist[i].clear();
		pathArr[i].clear();
		//pathEndAtSum[i] = 0LL;
		//pathEndAtCnt[i] = 0;
		order temp;
		cin >> A >> B >> X >> Y;
		temp.bD = A;
		temp.sD = B;
		temp.bP = X;
		temp.sP = Y;
		orders.push_back(temp);
		auto lclmapit = buyorders.find(A);
		if(lclmapit == buyorders.end()){
			multimap<int, int> daymap;
			daymap.insert(pair<int, int>(X, i));
			buyorders.insert(pair<int, multimap<int, int>>(A, daymap));
		} else {
			(lclmapit->second).insert(pair<int, int>(X, i));
		}
		processOrder.insert(pair<int, int>(A, i));
	}
#if DEBUG
	for(auto it = sellorders.begin(); it != sellorders.end(); it++){
		cout << it->first << ": ";
		for(auto it2 = it->second.begin(); it2 != it->second.end(); it2++){
			cout << "(" << it2->first << ", " << it2->second << "), ";
		}
		cout << endl;
	}
#endif
#if PRINT_PROGRESS
	cout << "IO DONE" << endl;
#endif
/*
	for(int i = 0; i < N; i++){
		order lclorder = orders[i];
#if PRINT_PROGRESS
		if(i % 1000 == 0){
			cout << "Processed " << i << ", pc=" << procCount <<  endl;
		}
#endif
		auto matchingsellordersit = sellorders.find(lclorder.bD);
		if(matchingsellordersit != sellorders.end()){
#if PRINT_PROGRESS
			procCount++;
#endif
			int buyPrice = lclorder.bP;
			auto endit = (matchingsellordersit->second).lower_bound(buyPrice);
			for(auto it = (matchingsellordersit->second).begin(); it != endit; it++){
				int profit = buyPrice - it->first;
				adjlist[it->second].push_back(pair<int, int>(i, profit)); // pair (target, profit)
			}
		}
	}
#if PRINT_PROGRESS
	cout << "GRAPH BUILDING DONE" << endl;
#endif
#if DEBUG
	for(int i = 0; i < N; i++){
		cout << "possible ppl " << i << " can sell to: ";
		for(auto it = adjlist[i].begin(); it != adjlist[i].end(); it++){
			cout << "(" << it->first << ", " << it->second << "), ";
		}
		cout << endl;
	}
#endif
*/
	for(auto it = processOrder.begin(); it != processOrder.end(); it++){
		int curNode = it->second;
		int targetProfit, targetNode, newProfit;
#if PRINT_PROGRESS
		if(oT % 1000 == 999){
			cout << "Processing " << curNode << endl;
		}
		oT++;
#endif
		int curShortestPath = paths[0];
		for(auto it2 = adjlist[curNode].begin(); it2 != adjlist[curNode].end(); it2++){
			targetNode = it2->first;
			targetProfit = it2->second;
			pathArr[targetNode].insert(targetProfit);
			paths.insert(targetProfit);
			if(paths.size() > K){
				paths.erase(paths.begin());
			}
			if(pathArr[targetNode].size() > K){
				pathArr[targetNode].erase(pathArr[targetNode].begin());
			}
			for(auto it3 = pathArr[curNode].begin(); it3 != pathArr[curNode].end(); it3++){
				newProfit = *it3 + targetProfit;
				pathArr[targetNode].insert(newProfit);
				paths.insert(newProfit);
				if(paths.size() > K){
					paths.erase(paths.begin());
				}
				if(pathArr[targetNode].size() > K){
					pathArr[targetNode].erase(pathArr[targetNode].begin());
				}
			}
/*
			pathEndAtCnt[targetNode] += pathStartAtCurNodeCnt;
			pathEndAtSum[targetNode] += pathEndAtSum[curNode];
			pathEndAtSum[targetNode] += pathStartAtCurNodeCnt * ((long long)(it2->second));
			pathEndAtSum[targetNode] %= MOD;
*/
		}
	}
	long long sum = 0LL;
	for(auto it = paths.begin(); it != paths.end(); it++){
		sum += *it;
	}
	cout << sum << endl;
}

int main(){
	cin.tie(NULL);
	ios_base::sync_with_stdio(false);
	int T;
	cin >> T;
	for(int i = 1; i <= T; i++){
		doCase(i);
	}
	return 0;
}
