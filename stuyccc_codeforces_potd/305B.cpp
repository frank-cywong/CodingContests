#include <iostream>

using namespace std;

typedef long long ll;

ll gcf(ll a, ll b){
	while(true){
		a %= b;
		if(a == 0){
			return b;
		}
		ll temp = a;
		a = b;
		b = temp;
	}
}

ll coeffs[90];

int main(){
	ll p, q;
	cin >> p >> q;
	int n;
	cin >> n;
	ll temp;
	for(int i = 0; i < n; i++){
		cin >> temp;
		coeffs[i] = temp;
	}
	ll num = coeffs[n - 1];
	ll denom = 1LL;
	for(int i = (n - 2); i >= 0; i--){
		if(num > 4000000000000000000LL || denom > 4000000000000000000LL){
			cout << "NO" << endl;
			return 0;
		}
		ll temp = num;
		num = denom;
		denom = temp;
		ll next = coeffs[i];
		ll nTop = next * denom;
		if((next != 0 && nTop / next != denom) || nTop > 4000000000000000000LL){
			cout << "NO" << endl;
			return 0;
		}
		num += nTop;
	}
	ll gcfPQ = gcf(p, q);
	p /= gcfPQ;
	q /= gcfPQ;
	if(num == p && denom == q){
		cout << "YES" << endl;
	} else {
		cout << "NO" << endl;
	}
	return 0;
}
