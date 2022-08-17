#include <iostream>

using namespace std;

long long gcf(long long a, long long b){
	while(true){
		a %= b;
		if(a == 0){
			return b;
		}
		long long temp = a;
		a = b;
		b = temp;
	}
}

int main(){
	int n, d, e;
	cin >> n >> d >> e;
	e *= 5;
	int gcfV = (int)gcf(d, e);
	// reduce everything by gcf
	int o = n % gcfV;
	n /= gcfV;
	d /= gcfV;
	e /= gcfV;
	int mcNugget = d * e - d - e;
	if(n > mcNugget){
		cout << o;
		return 0;
	}
	int curMin = n;
	for(int i = 0; i < e; i++){
		if(d * i > n){
			break;
		}
		int rem = (n - d * i) % e;
		if(rem >= 0 && rem < curMin){
			curMin = rem;
		}
	}
	o += (gcfV * curMin);
	cout << o;
	return 0;
}
