#include <iostream>
#include <random>

using namespace std;

typedef long long ll;

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	ll n;
	int k;
	cin >> n;
	cin >> k;
	ll l = 1;
	ll r = n;
	int cutRange = 4 * k + 1;
	//minstd_rand0 rnGen (1227992885);
	int seed = 15199;
	string res;
	int rN = 15199;
	while(true){
		if(l < 1LL){
			l = 1LL;
		}
		if(r > n){
			r = n;
		}
		if(r - l + 1 > (cutRange)){
			ll m = (r + l);
			m >>= 1;
			cout << l << " " << m << endl;
			cin >> res;
			if(res == "Bad"){
				break;
			}
			if(res == "Yes"){
				l -= k;
				r = (m + k);
			} else {
				l = (m - k + 1);
				r += k;
			}
		} else {
			if(l == r){
				cout << l << " " << l << endl;
			} else {
				//int rN = rnGen();
				rN = seed;
				seed <<= 3;
				seed %= 62491;
				rN %= (r - l + 1);
				ll guess = l + rN;
				cout << guess << " " << guess << endl;
			}
			cin >> res;
			if(res != "No"){
				break;
			}
			l -= k;
			r += k;
		}
	}
	return 0;
}
