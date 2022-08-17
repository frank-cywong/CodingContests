#include <iostream>
#include <vector>

using namespace std;

vector<int> adj[300001];

int strengths[300001]; // 1-indexed

int n;

int main(){
	cin >> n;
	int tempa, tempb;
	for(int i = 1; i <= n; i++){
		cin >> tempa;
		strengths[i] = tempa;
	}
	for(int i = 1; i < n; i++){
		cin >> tempa >> tempb;
		adj[tempa].push_back(tempb);
		adj[tempb].push_back(tempa);
	}
	return 0;
}
