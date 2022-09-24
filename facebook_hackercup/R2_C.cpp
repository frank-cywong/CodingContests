#include <iostream>
#include <vector>

#define DEBUG 0

using namespace std;

typedef long long ll;

ll MOD = 1000000007LL;

vector<ll> factorialCache;

ll fact(ll x){
	if(x < factorialCache.size()){
		return factorialCache[x];
	} else {
		ll o = factorialCache[factorialCache.size() - 1];
		for(ll i = factorialCache.size(); i <= x; i++){
			o *= i;
			o %= MOD;
			factorialCache.push_back(o);
		}
		return o;
	}
}

ll bin_pow(ll b, ll e, ll mod) {
    b %= mod;
    e %= mod - 1;
    if(b < 0) b += mod;
    if(e < 0) e += mod - 1;
    ll r = 1;
    while(e) {
        if(e & 1) r = (r * b) % mod;
        b = (b * b) % mod;
        e >>= 1;
    }
    return r;
}

ll modInvAlt(ll A, ll M) {
	return bin_pow(A, M - 2, MOD);
}

// Function for extended Euclidean Algorithm
ll gcdExtended(ll a, ll b, ll* x, ll* y);
 
// Function to find modulo inverse of a
ll modInverse(ll A, ll M)
{
    ll x, y;
    ll g = gcdExtended(A, M, &x, &y);
    if (g != 1)
        return -1;
    else {
 
        // m is added to handle negative x
        ll res = (x % M + M) % M;
        return res;
    }
}
 
// Function for extended Euclidean Algorithm
ll gcdExtended(ll a, ll b, ll* x, ll* y)
{
 
    // Base Case
    if (a == 0) {
        *x = 0, *y = 1;
        return b;
    }
 
    // To store results of recursive call
    ll x1, y1;
    ll gcd = gcdExtended(b % a, a, &x1, &y1);
 
    // Update x and y using results of recursive
    // call
    *x = y1 - (b / a) * x1;
    *y = x1;
 
    return gcd;
}

ll nPr(ll a, ll b){
	if(b > a){
		return 0LL;
	}
	ll fa = fact(a);
	ll fb = fact(a - b);
	ll mb = modInverse(fb, MOD);
	return ((fa * mb) % MOD);
}

void doCase(int t){
	int N, K;
	cin >> N >> K;
	cout << "Case #" << t << ": ";
	int C, W;
	int C1V;
	int C1C;
	int LCC = 0; // < C1
	int LEC = 0; // <= C1
	int EEC = 0; // == C1
	int TC = 0; // anything
	for(int i = 0; i < N; i++){
		cin >> C >> W;
		if(i == 0){
			C1V = W;
			C1C = C;
		}
		TC += C;
		if(W < C1V){
			LCC += C;
			LEC += C;
		} else if (W == C1V){
			LEC += C;
			EEC += C;
		}
	}
#if DEBUG
	cout << "TEST: " << C1C << " " << C1V << " " << LCC << " " << LEC << " " << EEC << " " << TC << endl;
#endif
	ll output = nPr(LEC, K+1);
	output -= nPr(LCC, K+1);
	output += MOD;
	output %= MOD;
	output *= C1C;
	output %= MOD;
	output *= modInverse(EEC, MOD);
	output %= MOD;
	output *= modInverse(nPr(TC, K+1), MOD);
	output %= MOD;
	cout << output << endl;
}

int main(){
	factorialCache.push_back(1);
	int T;
	cin >> T;
	for(int i = 1; i <= T; i++){
		doCase(i);
	}
	return 0;
}
