#include <iostream>
#include <vector>
#include <cstring>

using namespace std;

int level[65536];
vector<int> adj[65536];
int lvlcount[65536];
int maxLvl = 1;

void dfs(int node, int lvl){
	level[node] = lvl;
	lvlcount[lvl]++;
	if(lvl > maxLvl){
		maxLvl = lvl;
	}
	for(auto it = adj[node].begin(); it != adj[node].end(); it++){
		if(level[*it] == 0){
			dfs(*it, lvl + 1);
		}
	}
}

void doCase(int t){
	int N, Q;
	cin >> N >> Q;
	for(int i = 0; i < 65536; i++){
		adj[i].clear();
	}
	int ti, tj;
	for(int i = 0; i < N - 1; i++){
		cin >> ti >> tj;
		adj[ti].push_back(tj);
		adj[tj].push_back(ti);
	}
	memset(level, 0, sizeof(int) * 65536);
	memset(lvlcount, 0, sizeof(int) * 65536);
	dfs(1, 1);
	for(int i = 0; i < Q; i++){
		cin >> ti;
	}
	int cursum = 0;
	for(int i = 1; i <= maxLvl; i++){
		int extra = lvlcount[i];
		if(cursum + extra > Q){
			cout << "Case #" << t << ": " << cursum << endl;
			return;
		}
		cursum += extra;
	}
	cout << "Case #" << t << ": " << N << endl;
	return;
}

int main(){
	int T;
	cin >> T;
	for(int i = 1; i <= T; i++){
		doCase(i);
	}
	return 0;
}
