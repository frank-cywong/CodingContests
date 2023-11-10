#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>

using namespace std;

vector<int> coords;

void doCase(int t){
	cout << "Case #" << t << ": ";
	int N;
	cin >> N;
	coords.clear();
	for(int i = 0; i < N; ++i){
		int x;
		cin >> x;
		coords.push_back(x);
	}
	sort(coords.begin(), coords.end());
	/*
	cout << "DEBUG: ";
	for(auto it = coords.begin(); it != coords.end(); ++it){
		cout << *it << " ";
	}
	cout << endl;
	*/
	if(N == 5){
		double rv1 = coords[4] + coords[2] - coords[1] - coords[0];
		rv1 /= 2.0;
		double rv2 = coords[4] + coords[3] - coords[2] - coords[0];
		rv2 /= 2.0;
		if(rv2 > rv1){
			rv1 = rv2;
		}
		cout << rv1 << endl;
	} else {
		double i1 = coords[1] + coords[0];
		i1 /= 2.0;
		double i2 = coords[N-1] + coords[N-2];
		i2 /= 2.0;
		cout << (i2 - i1) << endl;
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