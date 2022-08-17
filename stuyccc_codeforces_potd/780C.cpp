#include <iostream>
#include <vector>

using namespace std;

vector<int> adj[200001]; // 1-indexing
bool visited[200001];
int k = 1;
int colours[200001];

void dfs(int node, int ancestorColour){
	visited[node] = true;
	int coloursNeeded = adj[node].size() + 1;
	if(k < coloursNeeded){
		k = coloursNeeded;
	}
	int selfColour = colours[node];
	int curColour = 1;
	for(auto it = adj[node].begin(); it != adj[node].end(); it++){
		if(visited[*it]){
			continue;
		}
		while(curColour == selfColour || curColour == ancestorColour){
			curColour++;
		}
		colours[*it] = curColour;
		curColour++;
		dfs(*it, selfColour);
	}
}

int main(){
	int n;
	cin >> n;
	int x, y;
	for(int i = 0; i < n - 1; i++){
		cin >> x >> y;
		adj[x].push_back(y);
		adj[y].push_back(x);
	}
	colours[1] = 1;
	dfs(1, -1);
	cout << k << endl;
	for(int i = 1; i <= n; i++){
		cout << colours[i] << " ";
	}
}
