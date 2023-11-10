#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>
#include <cmath>

using namespace std;

vector<int> factors;

void doCase(int t){
	int P;
	cin >> P;
	factors.clear();
	while(P % 2 == 0){
		P /= 2;
		factors.push_back(2);
	}
	for(int i = 3; i <= sqrt(P); i += 2){
		while(P % i == 0){
			P /= i;
			factors.push_back(i);
		}
	}
	if(P != 1){
		factors.push_back(P);
	}
	/*
	cout << "DEBUG: ";
	for(auto it = factors.begin(); it != factors.end(); ++it){
		cout << *it << " ";
	}
	cout << endl;
	*/
	int factorsum = 0;
	int factorcount = 0;
	for(auto it = factors.begin(); it != factors.end(); ++it){
		factorsum += *it;
		++factorcount;
	}
	cout << "Case #" << t << ": ";
	if(factorsum > 41){
		cout << -1 << "\n";
		return;
	}
	int tc = (41 - factorsum + factorcount);
	cout << tc << " ";
	while(factorsum < 41){
		cout << "1 ";
		++factorsum;
		--tc;
	}
	for(auto it = factors.begin(); it != factors.end(); ++it){
		if(tc != 1){
			cout << *it << " ";
		} else {
			cout << *it;
		}
		--tc;
	}
	cout << endl;
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