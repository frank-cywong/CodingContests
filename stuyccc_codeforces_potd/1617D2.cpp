#include <iostream>
#include <cstdlib>
#include <cstring>
#include <ios>

using namespace std;

int query(int a, int b, int c){
	cout << "? " << a << ' ' << b << ' ' << c << '\n';
	cout.flush();
	int res;
	cin >> res;
	if(res == -1){
		exit(1);
	}
	return res;
}

void doCase(){
	int n;
	cin >> n;
	if(n == -1){
		exit(2);
	}
	const int IMPOSTER_DOMINATED = 0;
	const int CREWMATE_DOMINATED = 1;
	const int STATUS_UNKNOWN = -1;
	const int STATUS_IMPOSTER = 0;
	const int STATUS_CREWMATE = 1;
	int status[10001];
	memset(status, STATUS_UNKNOWN, sizeof(int) * 10001);
	int startPairType = query(1, 2, 3);
	int pairType = startPairType;
	int curTestPair = 0;
	for(curTestPair = 1; curTestPair < (n / 3); curTestPair++){
		pairType = query(curTestPair * 3 + 1, curTestPair * 3 + 2, curTestPair * 3 + 3);
		if(pairType != startPairType){
			break;
		}
	}
	if(pairType == startPairType){
		exit(3);
	}
	int imposterDomPair = (startPairType == IMPOSTER_DOMINATED ? 0 : curTestPair);
	int crewmateDomPair = (startPairType == IMPOSTER_DOMINATED ? curTestPair : 0);
	int valA = imposterDomPair * 3 + 1;
	int valB = imposterDomPair * 3 + 2;
	int valC = imposterDomPair * 3 + 3;
	int valD = crewmateDomPair * 3 + 1;
	int valE = crewmateDomPair * 3 + 2;
	int valF = crewmateDomPair * 3 + 3;
	int res = query(valA, valB, valD);
	int knownImposter = -1;
	int knownCrewmate = -1;
	if(res == IMPOSTER_DOMINATED){
		res = query(valA, valB, valE);
		if(res == IMPOSTER_DOMINATED){
			status[valA] = STATUS_IMPOSTER;
			status[valB] = STATUS_IMPOSTER;
			res = query(valA, valD, valE);
			if(res == IMPOSTER_DOMINATED){
				status[valF] = STATUS_CREWMATE;
				knownImposter = valA;
				knownCrewmate = valF;
				res = query(valA, valC, valF);
				if(res == IMPOSTER_DOMINATED){
					status[valC] = STATUS_IMPOSTER;
				} else {
					status[valC] = STATUS_CREWMATE;
				}
				res = query(valA, valD, valF);
				if(res == IMPOSTER_DOMINATED){
					status[valD] = STATUS_IMPOSTER;
				} else {
					status[valD] = STATUS_CREWMATE;
				}
				res = query(valA, valE, valF);
				if(res == IMPOSTER_DOMINATED){
					status[valE] = STATUS_IMPOSTER;
				} else {
					status[valE] = STATUS_CREWMATE;
				}
			} else {
				status[valD] = STATUS_CREWMATE;
				status[valE] = STATUS_CREWMATE;
				knownImposter = valA;
				knownCrewmate = valD;
				res = query(valA, valC, valD);
				if(res == IMPOSTER_DOMINATED){
					status[valC] = STATUS_IMPOSTER;
				} else {
					status[valC] = STATUS_CREWMATE;
				}
				res = query(valA, valF, valD);
				if(res == IMPOSTER_DOMINATED){
					status[valF] = STATUS_IMPOSTER;
				} else {
					status[valF] = STATUS_CREWMATE;
				}
			}
		} else {
			status[valC] = STATUS_IMPOSTER;
			status[valD] = STATUS_IMPOSTER;
			status[valE] = STATUS_CREWMATE;
			status[valF] = STATUS_CREWMATE;
			knownImposter = valD;
			knownCrewmate = valE;
			res = query(valA, valD, valE);
			if(res == IMPOSTER_DOMINATED){
				status[valA] = STATUS_IMPOSTER;
				status[valB] = STATUS_CREWMATE;
			} else {
				status[valA] = STATUS_CREWMATE;
				status[valB] = STATUS_IMPOSTER;
			}
		}
	} else { // res is CREWMATE_DOMINATED, ie. valD is crew, valC is imposter
		res = query(valA, valC, valD);
		status[valC] = STATUS_IMPOSTER;
		status[valD] = STATUS_CREWMATE;
		knownImposter = valC;
		knownCrewmate = valD;
		if(res == IMPOSTER_DOMINATED){
			status[valA] = STATUS_IMPOSTER;
			status[valB] = STATUS_CREWMATE;
		} else {
			status[valA] = STATUS_CREWMATE;
			status[valB] = STATUS_IMPOSTER;
		}
		res = query(valC, valD, valE);
		if(res == IMPOSTER_DOMINATED){
			status[valE] = STATUS_IMPOSTER;
			status[valF] = STATUS_CREWMATE;
		} else {
			status[valE] = STATUS_CREWMATE;
			res = query(valC, valD, valF);
			if(res == IMPOSTER_DOMINATED){
				status[valF] = STATUS_IMPOSTER;
			} else {
				status[valF] = STATUS_CREWMATE;
			}
		}
	}
	// now deal with groups in between, we all know they are STATUS_IMPOSTER or STATUS_CREWMATE based on startPairType
	for(int i = 1; i < curTestPair; i++){
		if(startPairType == IMPOSTER_DOMINATED){
			res = query(knownCrewmate, i * 3 + 1, i * 3 + 2);
			if(res == IMPOSTER_DOMINATED){
				status[i * 3 + 1] = STATUS_IMPOSTER;
				status[i * 3 + 2] = STATUS_IMPOSTER;
				status[i * 3 + 3] = query(knownCrewmate, knownImposter, i * 3 + 3);
			} else {
				status[i * 3 + 3] = STATUS_IMPOSTER;
				res = query(knownCrewmate, knownImposter, i * 3 + 1);
				if(res == IMPOSTER_DOMINATED){
					status[i * 3 + 1] = STATUS_IMPOSTER;
					status[i * 3 + 2] = STATUS_CREWMATE;
				} else {
					status[i * 3 + 1] = STATUS_CREWMATE;
					status[i * 3 + 2] = STATUS_IMPOSTER;
				}
			}
		} else {
			res = query(knownImposter, i * 3 + 1, i * 3 + 2);
			if(res == CREWMATE_DOMINATED){
				status[i * 3 + 1] = STATUS_CREWMATE;
				status[i * 3 + 2] = STATUS_CREWMATE;
				status[i * 3 + 3] = query(knownCrewmate, knownImposter, i * 3 + 3);
			} else {
				status[i * 3 + 3] = STATUS_CREWMATE;
				res = query(knownCrewmate, knownImposter, i * 3 + 1);
				if(res == IMPOSTER_DOMINATED){
					status[i * 3 + 1] = STATUS_IMPOSTER;
					status[i * 3 + 2] = STATUS_CREWMATE;
				} else {
					status[i * 3 + 1] = STATUS_CREWMATE;
					status[i * 3 + 2] = STATUS_IMPOSTER;
				}
			}
		}
	}
	for(int i = curTestPair * 3 + 4; i <= n; i++){
		status[i] = query(knownImposter, knownCrewmate, i);
	}
	cout << "! ";
	int impCounter = 0;
	for(int i = 1; i <= n; i++){
		if(status[i] == STATUS_IMPOSTER){
			impCounter++;
		}
	}
	cout << impCounter;
	for(int i = 1; i <= n; i++){
		if(status[i] == STATUS_IMPOSTER){
			cout << " " << i;
		}
	}
	cout << endl;
}

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	int t;
	cin >> t;
	for(int i = 0; i < t; i++){
		doCase();
	}
	return 0;
}
