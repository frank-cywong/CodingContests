#include <iostream>
#include <cmath>

using namespace std;

bool is_prime(int n){
	int sqrtn = (int)(sqrt((double)(n)));
	for(int p = 2; p <= sqrtn; p++){
		if(n % p == 0){
			return false;
		}
	}
	return true;
}

int main(){
	int n;
	cin >> n;
	if(is_prime(n)){
		cout << 1;
	} else if(n % 2 == 0){
		cout << 2;
	} else if(is_prime(n - 2)){
		cout << 2;
	} else {
		cout << 3;
	}
	return 0;
}
