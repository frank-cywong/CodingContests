#include <iostream>
#include <vector>
#include <iomanip>
#include <map>
#include <algorithm>

using namespace std;

bool visited[101];
vector<int> adj[101];

vector<int> numbers;

map<vector<int>, bool> caseWorksDP;

bool recursiveDPRegular(vector<int> toCheck, int startPos, int numbersSize, int N, int K, int rPS){
	sort(toCheck.begin(), toCheck.end());
	auto it = caseWorksDP.find(toCheck);
	if(it != caseWorksDP.end()){
		return it->second;
	}
	// if you get here toCheck is all 0
	if(startPos == numbersSize){
		caseWorksDP[toCheck] = true;
		return true;
	}
	int addVal = numbers[startPos];
	for(int i = 0; i < K; ++i){
		if(toCheck[i] >= addVal){
			vector<int> copyToCheck(toCheck);
			copyToCheck[i] -= addVal;
			if(recursiveDPRegular(copyToCheck, startPos + 1, numbersSize, N, K, rPS)){
				caseWorksDP[toCheck] = true;
				return true;
			}
		}
	}
	caseWorksDP[toCheck] = false;
	return false;
}

bool regularCase(int N, int K){
	caseWorksDP.clear();
	int reqPerSlot = N / K;
	vector<int> target;
	for(int i = 0; i < K; ++i){
		target.push_back(reqPerSlot);
	}
	return recursiveDPRegular(target, 0, numbers.size(), N, K, reqPerSlot);
}

bool smallGroupCase(int N, int reqPerSlot){
	if(reqPerSlot == 2){
		// guaranteed to work by prev conditions
		return true;
	}
	// make a freq table
	vector<int> fT;
	for(int i = 0; i <= reqPerSlot; ++i){
		fT.push_back(0);
	}
	for(auto it = numbers.begin(); it != numbers.end(); ++it){
		fT[*it] += 1;
	}
	if(reqPerSlot == 3){
		// all groups are size 3 or less
		// must have at least as many size 1 gps as size 2 ones
		if(fT[1] >= fT[2]){
			return true;
		} else {
			return false;
		}
	}
	if(reqPerSlot == 4){
		// all groups are size 4 or less
		// must have at least as many size 1 gps as size 3 gps
		// if (# of size 2 gps) is odd, also must have 2 more size 1 gps
		int c3 = fT[3];
		int c2 = fT[2];
		int c1 = fT[1];
		if(c3 > c1){
			return false;
		}
		c1 -= c3;
		if(c2 % 2 == 1 && c1 < 2){
			return false;
		}
		return true;
	}
	if(reqPerSlot == 5){
		// all groups are size 5 or less
		// must have at least as many size 1 gps as size 4 gps
		// greedily use size 2 gps to fill size 3 gps
		// cover up rest with size 1 gps
		int c4 = fT[4];
		int c3 = fT[3];
		int c2 = fT[2];
		int c1 = fT[1];
		if(c4 > c1){
			return false;
		}
		c1 -= c4;
		int c2fillc3 = c3;
		if(c2fillc3 > c2){
			c2fillc3 = c2;
		}
		c3 -= c2fillc3;
		c2 -= c2fillc3;
		if(c3 != 0){ // all c2 gone however
			int reqc1 = c3 * 2;
			if(c1 < reqc1){
				return false;
			}
			c1 -= reqc1;
			c3 = 0;
		}
		if(c2 != 0){
			// try 2, 2, 1 first
			int c2_2groups = c2 / 2;
			int reqc1 = c2_2groups;
			if(c2 % 2 == 1){ // 2, 1, 1, 1
				reqc1 += 3;
			}
			if(c1 < reqc1){
				return false;
			}
		}
		return true;
	}
	// all groups are size 6 or less
	// must have at least as many size 1 gps to fill size 5 gps
	int c5 = fT[5];
	int c4 = fT[4];
	int c3 = fT[3];
	int c2 = fT[2];
	int c1 = fT[1];
	//cout << "DEBUG: " << c1 << " " << c2 << " " << c3 << " " << c4 << " " << c5 << endl;
	if(c5 > c1){
		return false;
	}
	c1 -= c5;
	// greedily use size 2 gps to fill size 4 gps
	int c2fillc4 = c4;
	if(c2fillc4 > c2){
		c2fillc4 = c2;
	}
	c4 -= c2fillc4;
	c2 -= c2fillc4;
	// size 4 gps left? use size 1 gps
	if(c4 > 0){
		int reqc1 = c4 * 2;
		if(c1 < reqc1){
			return false;
		}
		c1 -= reqc1;
		c4 = 0;
	}
	// size 3 groups try to pair with each other if possible
	// if odd then try 3, 2, 1 before 3, 1, 1, 1
	c3 %= 2;
	if(c3 == 1){
		if(c2 == 0){
			if(c1 < 3){
				return false;
			}
			c3 -= 1;
			c1 -= 3;
		} else {
			if(c1 < 1){
				return false;
			}
			c3 -= 1;
			c2 -= 1;
			c1 -= 1;
		}
	}
	// size 2 groups pair with each other if possible
	c2 %= 3;
	// remainder with size 1;
	if(c2 != 0){
		int reqc1 = (6 - c2 * 2);
		if(c1 < reqc1){
			return false;
		}
		c1 -= reqc1;
		c2 = 0;
	}
	return true;
}

void dfs(int node, int numberind){
	numbers[numberind] += 1;
	visited[node] = true;
	for(auto it = adj[node].begin(); it != adj[node].end(); ++it){
		if(!visited[*it]){
			dfs(*it, numberind);
		}
	}
}

void doCase(int c){
	int N, M;
	cin >> N >> M;
	for(int i = 1; i <= 100; ++i){
		visited[i] = false;
		vector<int> v;
		adj[i] = v;
	}
	for(int i = 0; i < M; ++i){
		int a, b;
		cin >> a >> b;
		adj[a].push_back(b);
		adj[b].push_back(a);
	}
	numbers.clear();
	int maxgpsize = 1;
	int ci = 0;
	for(int i = 1; i <= N; ++i){
		if(!visited[i]){
			numbers.push_back(0);
			dfs(i, ci);
			++ci;
		}
	}
	for(auto it = numbers.begin(); it != numbers.end(); ++it){
		if(*it > maxgpsize){
			maxgpsize = *it;
		}
	}
	vector<int> toTestK;
	// 0 -> untested, 1 -> false, 2 -> true
	map<int, char> kWorks;
	int startTestCmd = N / maxgpsize;
	for(int i = startTestCmd; i >= 1; --i){
		if(N % i == 0){
			toTestK.push_back(i);
			kWorks[i] = 0;
		}
	}
	for(auto it = toTestK.begin(); it != toTestK.end(); ++it){
		if(kWorks[*it] != 0){
			continue;
		}
		if(*it == 1 || *it == N){
			kWorks[*it] = 2;
			continue;
		}
		int possibleK = *it;
		/*
		bool fail = false;
		for(int i = 2; i < possibleK; ++i){
			if(possibleK % i == 0){
				if(kWorks[i] != 2){
					fail = true;
				}
			}
		}
		if(fail){
			kWorks[*it] = 1;
			continue;
		}
		*/
		// actually need to test now
		int elementsPerGroup = N / possibleK;
		bool success = false;
		if(elementsPerGroup <= 6){
			success = smallGroupCase(N, elementsPerGroup);
		} else {
			success = regularCase(N, possibleK);
		}
		if(success){
			kWorks[*it] = 2;
			// every factor of this also works!
			int toFactor = *it;
			for(int i = 1; i < toFactor; ++i){
				if(toFactor % i == 0){
					kWorks[i] = 2;
				}
			}
		} else {
			kWorks[*it] = 1;
		}
	}
	cout << "Case #" << c << ":";
	for(auto it = toTestK.rbegin(); it != toTestK.rend(); ++it){
		if(kWorks[*it] == 2){
			cout << " ";
			cout << *it;
		}
	}
	cout << endl;
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