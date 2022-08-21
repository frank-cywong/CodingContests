#include <iostream>
#include <climits>
#include <cstring>

using namespace std;

typedef long long ll;

ll dp[21][10][10];
bool reachable[21][10][10];
char tollOP[4];
int tollK[4];

int N, P, M, Ar, Ac;

bool inRange(int x){
	return(x >= 0 && x < N);
}

void tick(int t){
	t--;
	for(int i = 0; i < N; i++){
		for(int j = 0; j < N; j++){
			if(!reachable[t][i][j]){
				continue;
			}
			reachable[t+1][i][j] = true;
			if(dp[t+1][i][j] < dp[t][i][j]){
				dp[t+1][i][j] = dp[t][i][j];
			}
			for(int dir = 0; dir < 4; dir++){
				// order: N, E, W, S
				int nI, nJ;
				switch(dir){
					case 0:
						nI = i - 1;
						nJ = j;
						break;
					case 1:
						nI = i;
						nJ = j + 1;
						break;
					case 2:
						nI = i;
						nJ = j - 1;
						break;
					case 3:
						nI = i + 1;
						nJ = j;
						break;
				}
				if(!inRange(nI) || !inRange(nJ)){
					continue;
				}
				ll newMoney = dp[t][i][j];
				char dirOP = tollOP[dir];
				ll dirK = (ll)(tollK[dir]);
				switch(dirOP){
					case '+':
						newMoney += dirK;
						break;
					case '-':
						newMoney -= dirK;
						break;
					case '*':
						newMoney *= dirK;
						break;
					case '/':
						if(newMoney < 0 && newMoney % dirK != 0){
							newMoney -= dirK;
						}
						newMoney /= dirK;
						break;
				}
				//cout << "COMPT newMoney = " << newMoney << ", " << t << ", " << nI << ", " << nJ << endl;
				reachable[t+1][nI][nJ] = true;
				if(newMoney > dp[t+1][nI][nJ]){
					dp[t+1][nI][nJ] = newMoney;
				}
			}
		}
	}
}

void doCase(int c){
	//memset(dp, LLONG_MIN, sizeof(ll) * 21 * 10 * 10);
	for(int i = 0; i < 21; i++){
		for(int j = 0; j < 10; j++){
			for(int k = 0; k < 10; k++){
				dp[i][j][k] = LLONG_MIN;
			}
		}
	}
	memset(reachable, false, sizeof(bool) * 21 * 10 * 10);
	cin >> N >> P >> M >> Ar >> Ac;
	reachable[0][Ar-1][Ac-1] = true;
	dp[0][Ar-1][Ac-1] = 0;
	for(int i = 0; i < 4; i++){
		char OP;
		int K;
		cin >> OP >> K;
		tollOP[i] = OP;
		tollK[i] = K;
	}
	for(int i = 0; i < P; i++){
		// to do
	}
	for(int t = 1; t <= M; t++){
		tick(t);
	}
	ll curMax = LLONG_MIN;
	for(int i = 0; i < N; i++){
		for(int j = 0; j < N; j++){
			if(!reachable[M][i][j]){
				continue;
			}
			if(dp[M][i][j] > curMax){
				curMax = dp[M][i][j];
			}
		}
	}
	cout << "Case #" << c << ": " << curMax << endl;
}

int main(){
	// assume P = 0 for now
	int T;
	cin >> T;
	for(int i = 1; i <= T; i++){
		doCase(i);
	}
	return 0;
}
