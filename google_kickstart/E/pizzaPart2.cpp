#include <iostream>
#include <climits>
#include <cstring>

using namespace std;

typedef long long ll;

ll dp[21][10][10][1024];
bool reachable[21][10][10][1024];
char tollOP[4];
int tollK[4];
int hasPizza[10][10];
int pizzas[10];

int N, P, M, Ar, Ac;

bool inRange(int x){
	return(x >= 0 && x < N);
}

void pizzaDeliveryCheck(int t){
	//cout << "pizz3aDeliveryCheck " << t << endl;
	for(int i = 0; i < N; i++){
		for(int j = 0; j < N; j++){
			for(int pc = 0; pc < (1 << P); pc++){
				if(!reachable[t][i][j][pc]){
					continue;
				}
				int hasPizzaVal = hasPizza[i][j];
				if(hasPizzaVal == -1){
					continue;
				}
				int pizzaBit = (1 << hasPizzaVal);
				if((pizzaBit & pc) != 0){
					continue;
				}
				//cout << "can deliver pizza: " << hasPizzaVal << endl;
				int newPizzaBit = pc | pizzaBit;
				//cout << "newPizzaBit: " << newPizzaBit << endl;
				reachable[t][i][j][newPizzaBit] = true;
				ll newMoney = pizzas[hasPizzaVal] + dp[t][i][j][pc];
				if(dp[t][i][j][newPizzaBit] < newMoney){
					dp[t][i][j][newPizzaBit] = newMoney;
				}
			}
		}
	}
}

void tick(int t){
	t--;
	for(int i = 0; i < N; i++){
		for(int j = 0; j < N; j++){
			for(int pc = 0; pc < (1 << P); pc++){
				if(!reachable[t][i][j][pc]){
					continue;
				}
				reachable[t+1][i][j][pc] = true;
				if(dp[t+1][i][j][pc] < dp[t][i][j][pc]){
					dp[t+1][i][j][pc] = dp[t][i][j][pc];
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
					ll newMoney = dp[t][i][j][pc];
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
					reachable[t+1][nI][nJ][pc] = true;
					if(newMoney > dp[t+1][nI][nJ][pc]){
						dp[t+1][nI][nJ][pc] = newMoney;
					}
				}
			}
		}
	}
	pizzaDeliveryCheck(t+1);
}

void doCase(int c){
	//memset(dp, LLONG_MIN, sizeof(ll) * 21 * 10 * 10);
	for(int i = 0; i < 21; i++){
		for(int j = 0; j < 10; j++){
			for(int k = 0; k < 10; k++){
				for(int l = 0; l < 1024; l++){
					dp[i][j][k][l] = LLONG_MIN;
				}
			}
		}
	}
	memset(reachable, false, sizeof(bool) * 21 * 10 * 10 * 1024);
	memset(hasPizza, -1, sizeof(int) * 10 * 10);
	memset(pizzas, 0, sizeof(int) * 10);
	cin >> N >> P >> M >> Ar >> Ac;
	reachable[0][Ar-1][Ac-1][0] = true;
	dp[0][Ar-1][Ac-1][0] = 0;
	for(int i = 0; i < 4; i++){
		char OP;
		int K;
		cin >> OP >> K;
		tollOP[i] = OP;
		tollK[i] = K;
	}
	int Xk, Yk, Ck;
	for(int i = 0; i < P; i++){
		cin >> Xk >> Yk >> Ck;
		hasPizza[Xk-1][Yk-1] = i;
		pizzas[i] = Ck;
	}
	for(int t = 1; t <= M; t++){
		tick(t);
	}
	ll curMax = LLONG_MIN;
	int neededP = ((1 << P) - 1);
	//cout << "neededP" << neededP << endl;
	bool impossible = true;
	for(int i = 0; i < N; i++){
		for(int j = 0; j < N; j++){
			if(!reachable[M][i][j][neededP]){
				continue;
			}
			impossible = false;
			if(dp[M][i][j][neededP] > curMax){
				curMax = dp[M][i][j][neededP];
			}
		}
	}
	cout << "Case #" << c << ": ";
	if(impossible){
		cout << "IMPOSSIBLE";
	} else {
		cout << curMax;
	}
	cout << endl;
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
