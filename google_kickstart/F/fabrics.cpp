#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

struct fabric{
	string C;
	int D;
	int U;
};

bool functionA(fabric a, fabric b){
	return(a.C == b.C ? (a.U < b.U) : (a.C < b.C));
}

bool functionB(fabric a, fabric b){
	return(a.D == b.D ? (a.U < b.U) : (a.D < b.D));
}

void doCase(int t){
	int N;
	cin >> N;
	vector<fabric> v;
	string temps;
	int tempd;
	int tempu;
	for(int i = 0; i < N; i++){
		cin >> temps >> tempd >> tempu;
		fabric tempf;
		tempf.C = temps;
		tempf.D = tempd;
		tempf.U = tempu;
		v.push_back(tempf);
	}
	vector<fabric> v2 = v;
	sort(v.begin(), v.end(), functionA);
	sort(v2.begin(), v2.end(), functionB);
	int count = 0;
	for(int i = 0; i < N; i++){
		if(v[i].U == v2[i].U){
			count++;
		}
	}
	cout << "Case #" << t << ": " << count << endl;
}

int main(){
	int T;
	cin >> T;
	for(int i = 1; i <= T; i++){
		doCase(i);
	}
	return 0;
}
