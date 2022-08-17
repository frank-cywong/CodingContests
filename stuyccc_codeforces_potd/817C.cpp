#include <iostream>

typedef long long ll;

using namespace std;

int digitsum(ll x){
	int counter = 0;
	while(x != 0){
		counter += (x % 10);
		x /= 10LL;
	}
	return counter;
}

int main(){
	ll n, s;
	cin >> n >> s;
	if(n <= s){
		cout << 0;
		return 0;
	}
	ll cutoff = s + 1;
	while(cutoff <= n && cutoff - digitsum(cutoff) < s){ // at most 18*9 evals, since cutoff must be within maximum digit sum (which is 18*9) of s
		cutoff++;
	}
	if(cutoff > n){
		cout << 0;
		return 0;
	}
	cout << (n - cutoff + 1);
	return 0;
}
