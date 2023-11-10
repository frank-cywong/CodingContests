#include <iostream>
#include <deque>
#include <vector>

int depth[250][250];
int cutday[250][250];

using namespace std;

int COORD_MULT = 300;

int DEPTH_MULT = COORD_MULT * COORD_MULT;

#define IN_RANGE(i, j, n) (i >= 0 && i < n && j >= 0 && j < n)

#define MUX(i, j, d) (i * COORD_MULT + j + d * DEPTH_MULT)

int get_depth(int i, int j, int n){
	if(!IN_RANGE(i, j, n)){
		return -2; // null
	}
	return depth[i][j];
}

int cus_ceil(int a, int b){
	return(a % b ? a / b + 1 : a / b);
}

void doCase(){
	int n;
	cin >> n;
	//cout << "N: " << n << endl;
	int k;
	cin >> k;
	int marked = 0;
	for(int i = 0; i < n; ++i){
		for(int j = 0; j < n; ++j){
			//cout << i << " " << j << endl;
			depth[i][j] = -1; // -1 for no tree
			cutday[i][j] = -1;
		}
	}
	// day count is either ceil(n/k) or max depth
	for(int i = 0; i < n; ++i){
		for(int j = 0; j < n; ++j){
			char x;
			cin >> x;
			if(x == 'T'){
				depth[i][j] = 0;
				cutday[i][j] = 0;
				++marked;
			}
		}
	}
	for(int i = 0; i < n; ++i){
		for(int j = 0; j < n; ++j){
			if(j != 0){
				cout << ' ';
			}
			cout << (depth[i][j] == -1 ? '.' : 'T');
		}
		cout << endl;
	}
	deque<int> toCheckNs;
	vector<vector<int>> cellsbydepth;
	vector<int> d1;
	for(int i = 0; i < n; ++i){
		for(int j = 0; j < n; ++j){
			if(depth[i][j] == 0 && (get_depth(i-1,j,n) <= -1 || get_depth(i,j-1,n) <= -1 || get_depth(i,j+1,n) <= -1 || get_depth(i+1,j,n) <= -1)){
				depth[i][j] = 1;
				if(get_depth(i-1,j,n) == 0){
					toCheckNs.push_back(MUX(i-1,j,2));
				}
				if(get_depth(i,j-1,n) == 0){
					toCheckNs.push_back(MUX(i,j-1,2));
				}
				if(get_depth(i,j+1,n) == 0){
					toCheckNs.push_back(MUX(i,j+1,2));
				}
				if(get_depth(i+1,j,n) == 0){
					toCheckNs.push_back(MUX(i+1,j,2));
				}
				d1.push_back(MUX(i,j,0));
			}
		}
	}
	cellsbydepth.push_back(d1);
	int maxdepth = 1;
	vector<int> cd;
	while(toCheckNs.size()){
		int tcn = toCheckNs.front();
		toCheckNs.pop_front();
		int d = tcn / DEPTH_MULT;
		tcn %= DEPTH_MULT;
		int iv = tcn / COORD_MULT;
		int jv = tcn % COORD_MULT;
		if(get_depth(iv, jv, n) == 0){
			depth[iv][jv] = d;
			if(get_depth(iv-1,jv,n) == 0){
				toCheckNs.push_back(MUX(iv-1,jv,d+1));
			}
			if(get_depth(iv,jv-1,n) == 0){
				toCheckNs.push_back(MUX(iv,jv-1,d+1));
			}
			if(get_depth(iv,jv+1,n) == 0){
				toCheckNs.push_back(MUX(iv,jv+1,d+1));
			}
			if(get_depth(iv+1,jv,n) == 0){
				toCheckNs.push_back(MUX(iv+1,jv,d+1));
			}
			if(maxdepth < d){
				if(maxdepth != 1){
					cellsbydepth.push_back(cd);
					cd = vector<int>();
				}
				maxdepth = d;
			}
			cd.push_back(MUX(iv, jv, 0));
		}
	}
	cellsbydepth.push_back(cd);
	int debugdepth = maxdepth;
	for(auto it = cellsbydepth.rbegin(); it != cellsbydepth.rend(); it++){
		cout << "List of locations with depth " << debugdepth << ": [";
		for(auto it2 = it->begin(); it2 != it->end(); it2++){
			if(it2 != it->begin()){
				cout << ", ";
			}
			cout << "(" << *it2 / COORD_MULT << ", " << *it2 % COORD_MULT << ")";
		}
		cout << "]" << endl;
		--debugdepth;
	}
	int movesneeded = maxdepth;
	if(cus_ceil(marked, k) > maxdepth){
		movesneeded = cus_ceil(marked, k);
	}
	int cur_write_depth = movesneeded;
	int cur_moves_left_at_depth = k;
	bool has_decreased_depth = false;
	for(auto it = cellsbydepth.rbegin(); it != cellsbydepth.rend(); it++){
		//cout << "List of locations with depth " << debugdepth << ": [";
		for(auto it2 = it->begin(); it2 != it->end(); it2++){
			int iv = *it2 / COORD_MULT;
			int jv = *it2 % COORD_MULT;
			cutday[iv][jv] = cur_write_depth;
			--cur_moves_left_at_depth;
			if(cur_moves_left_at_depth == 0){
				--cur_write_depth;
				cur_moves_left_at_depth = k;
			}
		}
		if(!has_decreased_depth){
			--cur_write_depth;
			cur_moves_left_at_depth = k;
		}
		//cout << "]" << endl;
	}
	for(int i = 0; i < n; ++i){
		for(int j = 0; j < n; ++j){
			if(j != 0){
				cout << ' ';
			}
			if(cutday[i][j] == -1){
				cout << '.';
			} else {
				cout << cutday[i][j];
			}
		}
		cout << endl;
	}
}

int main(){
	int t;
	cin >> t;
	for(int i = 0; i < t; ++i){
		doCase();
	}
	return 0;
}
