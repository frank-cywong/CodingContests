#include <iostream>
#include <ios>

using namespace std;

typedef long long ll;

const ll MOD = 1000000007LL;

ll modSq(ll x){
	x *= x;
	x %= MOD;
	return x;
}

void doCase(int t){
	cout << "Case #" << t << ": ";
	int N, Q;
	cin >> N;
	ll XSS = 0;
	ll DXS = 0;
	ll YSS = 0;
	ll DYS = 0;
	int A, B;
	for(int i = 0; i < N; i++){
		cin >> A >> B;
		DXS += A;
		DXS %= MOD;
		DYS += B;
		DYS %= MOD;
		XSS += modSq(A);
		XSS %= MOD;
		YSS += modSq(B);
		YSS %= MOD;
	}
	DXS *= 2;
	DXS %= MOD;
	DYS *= 2;
	DYS %= MOD;
	int X, Y;
	ll TXSS = 0;
	ll TYSS = 0;
	ll TDXS = 0;
	ll TDYS = 0;
	cin >> Q;
	for(int i = 0; i < Q; i++){
		cin >> X >> Y;
		TDXS += X;
		TDXS %= MOD;
		TDYS += Y;
		TDYS %= MOD;
		TXSS += modSq(X);
		TXSS %= MOD;
		TYSS += modSq(Y);
		TYSS %= MOD;
	}
	ll outputX = 0;
	outputX = Q;
	outputX *= XSS;
	outputX %= MOD;
	ll tempX = N;
	tempX *= TXSS;
	tempX %= MOD;
	outputX += tempX;
	outputX %= MOD;
	outputX -= (DXS * TDXS);
	outputX %= MOD;
	while(outputX < 0){
		outputX += MOD;
	}
	ll outputY = 0;
	outputY = Q;
	outputY *= YSS;
	outputY %= MOD;
	ll tempY = N;
	tempY *= TYSS;
	tempY %= MOD;
	outputY += tempY;
	outputY %= MOD;
	outputY -= (DYS * TDYS);
	outputY %= MOD;
	while(outputY < 0){
		outputY += MOD;
	}
	ll output = outputX + outputY;
	output %= MOD;
	cout << output << '\n';
	return;
}

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	int T;
	cin >> T;
	for(int i = 1; i <= T; i++){
		doCase(i);
	}
	return 0;
}
