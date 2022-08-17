#include <iostream>

typedef unsigned long long ull;

using namespace std;

int binlen(ull x){
	if((x & 0xFFFFFFFF00000000) == 0){
		//cout << "test@" << x << endl;
		return 32 - __builtin_clz(x & 0xFFFFFFFF);
	} else {
		//cout << "test!" << x << endl;
		return 64 - __builtin_clz(x >> 32);
	}
}

ull occurs(ull n, ull x){
	if(x == n){
		return 1;
	}
	ull curcount = 0;
	ull nexttier = (x % 2 == 0 ? 2 : 1);
	ull lbound = x;
	ull ubound = lbound + nexttier;
	while(n >= ubound){
		lbound <<= 1;
		ubound <<= 1;
		curcount |= nexttier;
		nexttier <<= 1;
		//cout << "n: " << n << ", ubound: " << ubound << endl;
	}
	if(n < lbound){
		return curcount;
	} else {
		return curcount + (n - lbound + 1);
	}
}

int main(){
	ull n, k;
	cin >> n >> k;
	if(k == 1){
		cout << n << endl;
		return 0;
	}
	if(k == 2){
		cout << (n % 2 == 1 ? n - 1 : n - 2) << endl;
		return 0;
	}
	//cout << binlen(n) << " " << binlen(k) << endl;
	//cout << occurs(11, 5) << endl;
	//cout << occurs(11, 4) << endl;
	//cout << binlen(5000000000) << endl;
	//cout << 0xFFFFFFFF00000000 << endl;
	//cout << 0xFFFFFFFF;
	// answer must be in range of 2^(binlen(n) - binlen(k)) and 2^(binlen(n) - binlen(k) + 2) (for each 2x numbers, at most 2x cases)
	ull lbound, ubound;
	lbound = ((ull) 1) << (binlen(n) - binlen(k));
	ubound = min(lbound << 2, n);
	//cout << "answer must be between: " << lbound << ", " << ubound << endl;
	ull olbound, oubound;
	olbound = (lbound % 2 == 0 ? lbound - 1 : lbound);
	oubound = min((ubound % 2 == 0 ? ubound + 1 : ubound), n);
	while(lbound != ubound){
		ull test = (lbound + ubound) / 2;
		if(test % 2 == 1){
			test++;
		}
		if(occurs(n, test) >= k){
			lbound = test;
		} else {
			ubound = test - 2;
		}
	}
	while(olbound != oubound){
		ull test = (olbound + oubound) / 2;
		if(test % 2 == 0){
			test++;
		}
		if(occurs(n, test) >= k){
			olbound = test;
		} else {
			oubound = test - 2;
		}
	}
	//cout << lbound << ", " << olbound << endl;
	cout << max(lbound, olbound) << endl;
	return 0;
}
