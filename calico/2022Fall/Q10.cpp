#include <iostream>
#include <cmath>
#include <cstdlib>
#include <string>

using namespace std;

void doCase(){
	cout << "P -1000 1000" << endl;
	double d1;
	cin >> d1;
	cout << "P 1000 1000" << endl;
	double d2;
	cin >> d2;
	d1 /= 2.0;
	d2 /= 2.0;
	double DO = sqrt(2.0) * 1000.0;
	d1 -= DO;
	d2 -= DO;
	double a = 4000000.0;
	a += (d1 * d1);
	a -= (d2 * d2);
	a /= 4000.0;
	double c = sqrt((d1 * d1) - (a * a));
	double steveX = a - 1000.0;
	cout << "P " << steveX << " " << (1000.0 + c) << endl;
	double d3;
	cin >> d3;
	d3 /= 2.0;
	d3 -= sqrt((steveX * steveX) + (1000.0 + c) * (1000.0 + c));
	if(d3 < c){
		cout << "B " << steveX << " " << (1000.0 + c) << endl;
	} else {
		cout << "B " << steveX << " " << (1000.0 - c) << endl;
	}
	string s;
	cin >> s;
	if(s == "WRONG_ANSWER"){
		exit(0);
	}
}

int main(){
	int T;
	cin >> T;
	for(int i = 0; i < T; ++i){
		doCase();
	}
	return 0;
}
