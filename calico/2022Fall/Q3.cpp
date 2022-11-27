#include <iostream>
#include <climits>

using namespace std;

void doCase(){
	int W, O, B, Ca, Cb, Cc;
	cin >> W >> O >> B >> Ca >> Cb >> Cc;
	if(Ca + Cb < Cc){
		Cc = Ca + Cb;
	}
	if(Ca + Cc < Cb){
		Cb = Ca + Cc;
	}
	if(Cb + Cc < Ca){
		Ca = Cb + Cc;
	}
	int CMin = INT_MAX;
	if((O * Ca + B * Cc) < CMin){
		CMin = O * Ca + B * Cc;
	}
	if((W * Ca + B * Cb) < CMin){
		CMin = W * Ca + B * Cb;
	}
	if((W * Cc + O * Cb) < CMin){
		CMin = W * Cc + O * Cb;
	}
	cout << CMin << endl;
}

int main(){
	int T;
	cin >> T;
	for(int i = 0; i < T; ++i){
		doCase();
	}
	return 0;
}
