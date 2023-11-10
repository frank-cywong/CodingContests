#include <iostream>
#include <vector>
#include <iomanip>

using namespace std;

char board[19][19];

vector<vector<int>> groups;
char visited[19][19];

const int MULT = 100;

int globR = 0;
int globC = 0;

void floodfill(int ind1, int ind2, int cmarker){
	if(ind1 < 0 || ind2 < 0 || ind1 >= globR || ind2 >= globC){
		return;
	}
	if(visited[ind1][ind2] || board[ind1][ind2] != 'W'){
		return;
	}
	visited[ind1][ind2] = 1;
	groups[cmarker].push_back(ind1 * MULT + ind2);
	//cout << "DEBUG: ADDED TILE (" << ind1 << ", " << ind2 << ") to group " << cmarker << endl;
	floodfill(ind1-1, ind2, cmarker);
	floodfill(ind1+1, ind2, cmarker);
	floodfill(ind1, ind2-1, cmarker);
	floodfill(ind1, ind2+1, cmarker);
}

void doCase(int ci){
	int R, C;
	cin >> R >> C;
	globR = R;
	globC = C;
	for(int i = 0; i < R; ++i){
		for(int j = 0; j < C; ++j){
			char tempc;
			cin >> tempc;
			board[i][j] = tempc;
			visited[i][j] = 0;
		}
	}
	groups.clear();
	int cmarker = 0;
	for(int i = 0; i < R; ++i){
		for(int j = 0; j < C; ++j){
			if(board[i][j] == 'W' && !visited[i][j]){
				vector<int> nv;
				groups.push_back(nv);
				floodfill(i, j, cmarker);
				++cmarker;
			}
		}
	}
	int maxwc = 0;
	for(auto it = groups.begin(); it != groups.end(); ++it){
		auto cvect = *it;
		int bndi = -1;
		int bndj = -1;
		char bnd_used = 0;
		char failflag = 0;
		for(auto it2 = cvect.begin(); it2 != cvect.end(); ++it2){
			int cval = *it2;
			int cvr = cval / MULT;
			int cvc = cval % MULT;
			int roffset[] = {-1, 0, 1, 0};
			int coffset[] = {0, -1, 0, 1};
			for(int i = 0; i < 4; ++i){
				int testr = cvr + roffset[i];
				int testc = cvc + coffset[i];
				if(testr >= 0 && testr < R && testc >= 0 && testc < C){
					if(board[testr][testc] == '.'){ // empty
						if(bnd_used && ((bndi != testr) || (bndj != testc))){
							// fail
							//cout << "DEBUG FAIL AT: " << testr << ", " << testc << " for tile (" << cvr << ", " << cvc << ")" << endl;
							failflag = 1;
							break;
						} else {
							bnd_used = 1;
							bndi = testr;
							bndj = testc;
						}
					}
				}
			}
			if(failflag){
				break;
			}
		}
		if(!failflag){
			int cwc = cvect.size();
			if(cwc > maxwc){
				maxwc = cwc;
			}
		}
	}
	if(maxwc != 0){
		cout << "Case #" << ci << ": YES" << endl;
	} else {
		cout << "Case #" << ci << ": NO" << endl;
	}
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