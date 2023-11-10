#include <iostream>
#include <vector>
#include <iomanip>
#include <map>
#include <algorithm>
#include <deque>

using namespace std;

map<int, vector<int>> edgeMLEs[1000001];
map<int, map<int, int>> edgeFTs[1000001];
map<int, int> totFTs[1000001];

vector<int> adj[1000001];
int parent[1000001];

deque<int> xfs_deque;
deque<int> xfs_actually_visit;
bool visited[1000001];

long long sum = 0;

inline int getEntryFromMap(map<int, int> &m, int key){
	if(m.find(key) != m.end()){
		return m[key];
	}
	return 0;
}

void freq_table_convert(int N){
	for(int i = 1; i <= N; ++i){
		map<int, int> totFT;
		for(auto it = edgeMLEs[i].begin(); it != edgeMLEs[i].end(); ++it){
			map<int, int> lclFT;
			int edgeTarget = it->first;
			vector<int> edgeCt = it->second;
			for(auto it2 = edgeCt.begin(); it2 != edgeCt.end(); ++it2){
				int v = *it2;
				lclFT[v] = getEntryFromMap(lclFT, v) + 1;
				totFT[v] = getEntryFromMap(totFT, v) + 1;
			}
			edgeFTs[i][edgeTarget] = lclFT;
		}
		totFTs[i] = totFT;
	}
}

void queue_bfs(int N){
	for(int i = 1; i <= N; ++i){
		visited[i] = false;
	}
	xfs_deque.clear();
	xfs_actually_visit.clear();
	xfs_deque.push_back(1);
	while(xfs_deque.size()){
		int f = xfs_deque.front();
		xfs_deque.pop_front();
		if(!visited[f]){
			visited[f] = true;
			xfs_actually_visit.push_back(f);
			for(auto it = adj[f].begin(); it != adj[f].end(); ++it){
				if(*it != parent[f]){
					xfs_deque.push_back(*it);
				}
			}
		}
	}
	while(xfs_actually_visit.size()){
		int b = xfs_actually_visit.back();
		xfs_actually_visit.pop_back();
		for(auto it = adj[b].begin(); it != adj[b].end(); ++it){
			if(*it == parent[b]){
				continue;
			}
			vector<int> eV;
			for(auto p = edgeMLEs[*it].begin(); p != edgeMLEs[*it].end(); ++p){
				vector<int> localV = p->second;
				eV.insert(eV.end(), localV.begin(), localV.end());
			}
			edgeMLEs[b][*it] = eV;
		}
	}
}

void queue_bfs2(int N){
	for(int i = 1; i <= N; ++i){
		visited[i] = false;
	}
	xfs_deque.clear();
	xfs_actually_visit.clear();
	xfs_deque.push_back(1);
	while(xfs_deque.size()){
		int f = xfs_deque.front();
		xfs_deque.pop_front();
		if(!visited[f]){
			visited[f] = true;
			xfs_actually_visit.push_back(f);
			for(auto it = adj[f].begin(); it != adj[f].end(); ++it){
				if(*it != parent[f]){
					xfs_deque.push_back(*it);
				}
			}
			// do process stuff
			if(parent[f]){
				map<int, int> pTFTCopy(totFTs[parent[f]]);
				for(auto it = totFTs[f].begin(); it != totFTs[f].end(); ++it){
					int k = it->first;
					int freq = it->second;
					pTFTCopy[k+1] -= freq;
				}
				for(auto it = pTFTCopy.begin(); it != pTFTCopy.end(); ++it){
					int k = it->first;
					int freq = it->second;
					map<int, int> nEFT;
					nEFT[k+1] = freq;
					totFTs[f][k+1] = getEntryFromMap(totFTs[f], k+1) + freq;
					edgeFTs[f][parent[f]] = nEFT;
				}
			}
		}
	}
}

void doCase(int c){
	int N;
	cin >> N;
	for(int i = 1; i <= N; ++i){
		edgeMLEs[i].clear();
		edgeFTs[i].clear();
		totFTs[i].clear();
		adj[i].clear();
	}
	parent[1] = 0;
	for(int i = 2; i <= N; ++i){
		int p;
		cin >> p;
		parent[i] = p;
		adj[p].push_back(i);
		adj[i].push_back(p);
	}
	cout << "DEBUG1" << endl;
	queue_bfs(N);
	cout << "DEBUG2" << endl;
	freq_table_convert(N);
	cout << "DEBUG3" << endl;
	queue_bfs2(N);
	cout << "DEBUG4" << endl;
	
}

int main(){
	cout << setprecision(32);
	int T;
	cin >> T;
	for(int i = 1; i <= 1000000; ++i){
		map<int, vector<int>> tiny;
		edgeMLEs[i] = tiny;
		map<int, int> fT;
		totFTs[i] = fT;
		map<int, map<int, int>> eFT;
		edgeFTs[i] = eFT;
	}
	for(int i = 1; i <= T; i++){
		doCase(i);
	}
	return 0;
}
