#include <iostream>
#include <cstring>
#include <set>

#define DEBUG 0

using namespace std;

typedef long long ll;

ll weightPrefixSums[6000];
int strengths[6000];
bool hasBox[6000];
//vector<int> possibleL;
set<int> possibleLSet;

void doCase(){
	int n;
	cin >> n;
	memset(hasBox, false, sizeof(bool) * 6000);
	possibleLSet.clear();
	int temp;
	for(int i = 0; i < n; i++){
		cin >> temp;
		if(i == 0){
			weightPrefixSums[i] = temp;
		} else {
			weightPrefixSums[i] = (weightPrefixSums[i-1]) + (long long)(temp);
		}
	}
	for(int i = 0; i < n; i++){
		cin >> temp;
		strengths[i] = temp;
	}
	int lastBoxPos = n-1;
	memset(hasBox, true, sizeof(bool) * n);
	long long moveCount = 0LL;
	int boxesLeft = n;
	possibleLSet.insert(0);
	while(boxesLeft > 0){
#if DEBUG
		cout << "STARTING LOOP WITH: " << boxesLeft << " BOXES LEFT" << endl;
#endif
		bool caseWorked = false;
		// claim: pushing right-most one won't harm at least
		auto it = possibleLSet.end();
		while(true){
			if(it == possibleLSet.begin()){
				break;
			}
			it--;
			int curTestL = *it;
#if DEBUG
			cout << "TESTING L: " << curTestL << endl;
#endif
			if(!hasBox[curTestL]){
				continue;
			}
			it++;
			int curTestR = ((it) == possibleLSet.end() ? lastBoxPos : *it - 1);
			it--;
			while(curTestR >= curTestL){
#if DEBUG
				cout << "TESTING R: " << curTestR << " FOR L: " << curTestL << endl;
#endif
				ll weightSum = weightPrefixSums[curTestR] - (curTestL == 0 ? 0 : weightPrefixSums[curTestL - 1]);
				if(weightSum <= (long long)(strengths[curTestR])){
#if DEBUG
					cout << "L : " << curTestL << ", R: " << curTestR << " WORKED" << endl;
#endif
					caseWorked = true;
					break;
				}
				curTestR--;
			}
			if(caseWorked){
				// handle updating values
				moveCount++;
				if(curTestL == 0){
					boxesLeft--;
					ll firstBoxWeight = weightPrefixSums[0];
					for(int i = 0; i <= lastBoxPos; i++){
						weightPrefixSums[i] -= firstBoxWeight;
					}
				}
				if(curTestR == lastBoxPos){
					lastBoxPos--;
				}
				for(int i = curTestL; i <= curTestR; i++){
					if(i == 0){
						continue;
					}
					hasBox[i - 1] = hasBox[i];
					weightPrefixSums[i - 1] = weightPrefixSums[i];
				}
				hasBox[curTestR] = false;
				// regen possibleL from scratch, inefficient but can be optimised later if needed
				//possibleL.clear();
#if DEBUG
				cout << "LAST BOX POS: " << lastBoxPos << endl;
				cout << "PREFIX SUMS: ";
				for(int i = 0; i <= lastBoxPos; i++){
					cout << weightPrefixSums[i] << " ";
				}
				cout << "\n HASBOX: ";
				for(int i = 0; i <= lastBoxPos; i++){
					cout << hasBox[i] << " ";
				}
				cout << endl;
#endif
				possibleLSet.erase(it);
				if(curTestR < lastBoxPos){
					possibleLSet.insert(curTestR+1);
				}
				if(hasBox[0]){
					possibleLSet.insert(0);
				}
/*
				for(int i = 0; i < lastBoxPos || i == 0; i++){
					if(i == 0 && hasBox[i]){
#if DEBUG
						cout << "ADDING i = 0 TO POSSIBLEL" << endl;
#endif
						possibleL.push_back(i);
					} else {
						if(!hasBox[i]){
#if DEBUG
							cout << "ADDING i = " << (i + 1) << " TO POSSIBLEL" << endl;
#endif
							possibleL.push_back(i + 1);
						}
					}
				}
*/
				break;
			}
		}
		if(!caseWorked){
			cout << -1 << endl;
			return;
		}
	}
	cout << moveCount << endl;
	return;
}

int main(){
	int t;
	cin >> t;
	for(int i = 0; i < t; i++){
		doCase();
	}
	return 0;
}
