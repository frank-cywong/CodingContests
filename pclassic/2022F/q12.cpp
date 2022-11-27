#include <vector>
#include <iostream>

#define TYPE_SH 0
#define TYPE_PP 1

using namespace std;

//int dp[10001][2][100]; // dp[i][j][k] is: considering the first i edges, with j being type (0 for shelter, 1 for powerplant) and id: k - number of connections for id l
//int dpCSum[100][100];

int distQ(int x0, int y0, int x1, int y1){
	int dx = (x1 - x0);
	int dy = (y1 - y0);
	return (dx * dx + dy * dy);
}

int findMaxPairing(int n, int m, vector<vector<int>> &shelterLocations, vector<vector<int>> &powerplantLocations, int p, int q, int o) {
	// m: # of powerplants
	// n: # of shelters
	// p: max S per P
	// q: min P per S
	// o: max P per S
	vector<vector<int>> PperS; // PperS[i] is a vector containing the working powerplants for each shelter
	vector<vector<int>> SperP; // SperP[i] is a vector containing the working shelters for each powerplant
	vector<vector<int>> edges; // vector containing all edges, edge[0] = SH, edge[1] = PP
	for(int i = 0; i < n; ++i){
		vector<int> v;
		PperS.push_back(v);
	}
	for(int i = 0; i < m; ++i){
		vector<int> v;
		SperP.push_back(v);
	}
	for(int i = 0; i < m; ++i){
		int PPx = powerplantLocations[i][0];
		int PPy = powerplantLocations[i][1];
		for(int j = 0; j < n; ++j){
			int SHx = shelterLocations[j][0];
			int SHy = shelterLocations[j][1];
			if(distQ(PPx, PPy, SHx, SHy) <= 100){
				PperS[j].push_back(i);
				SperP[i].push_back(j);
				vector<int> t_edge;
				t_edge.push_back(j);
				t_edge.push_back(i);
				edges.push_back(t_edge);
			}
		}
	}
	for(int i = 0; i < n; ++i){ // trivial failure case
		if(SperP[i].size() < q){
			return 0;
		}
	}
/*
	for(int i = 0; i <= edges.size(); ++i){
		for(int j = 0; j < 2; ++j){
			for(int k = 0; k < 100; ++k){
				dp[i][j][k] = 0;
			}
		}
	}
	for(int i = 0; i < edges.size(); ++i){
		// test every single of subedge cases
		int cmax = 0;
		int cmaxE = 0;
		for(int j = 0; j <= i; ++j){
		}
	}
	// assumption: if we maximise # of edges ignoring the minimum rule and a solution exists, the maximal case will be as much minimum as we can have
	// but does a solution exist?



	for(int i = 0; i < n; ++i){
		for(int j = 0; j < m; ++j){
			if(i == 0 && j == 0){
				for(int k = 0; k < 2; ++k){
					for(int l = 0; l < 100; ++l){
						dp[i][j][k][l] = 0;
					}
				}
				dpCSum = 0;
				continue;
			}
			int cmax = 0;
			int cmaxSubI = 0;
			int cmaxSubJ = 0;
			if(j == 0){
				cmax = dpCSum[i-1][j];
				cmaxSubI = i-1;
				cmaxSubJ = j;
			} else {
				cmax = dpCSum[i][j-1];
				cmaxSubI = i;
				cmaxSubJ = j;
			}
			for(int subI = 
		}
	}
*/
}

int main() {
	ios_base::sync_with_stdio(false); cin.tie(NULL);
	int t;
	cin >> t;
	while(t--) {
		int n;
		cin >> n;
		int m;
		cin >> m;
		vector<vector<int>> shelters(n, vector<int>(2));
		for(int i = 0; i < n; i++) {
			cin >> shelters[i][0] >> shelters[i][1];
		}
		vector<vector<int>> powerplants(m, vector<int>(2));
		for(int i = 0; i < m; i++) {
			cin >> shelters[i][0] >> shelters[i][1];
		}
		int p;
		cin >> p;
		int q;
		cin >> q;
		int o;
		cin >> o;
		cout << findMaxPairing(n, m, shelters, powerplants, p, q, o) << endl;
	}
	return 0;
}
