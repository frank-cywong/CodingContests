#include <iostream>
#include <cmath>

#define DEBUG 0

using namespace std;

void doCase(){
	int n, a, b;
	cin >> n >> a >> b;
	// solution to 2a <= nb, n integer, ie. n >= (2a/b), n >= ceil(2a/b)
	int goodToGoDownAt = ceil(2.0 * (double)(a) / (double)(b));
#if DEBUG
	cout << "goodToGoDownAt: " << goodToGoDownAt << endl;
#endif
	char temp;
	int lastPillar = -1;
	long long costCounter = 0;
	for(int i = 0; i < n; i++){
		cin >> temp;
		if(temp == '1'){
			if(lastPillar == -1){
				costCounter += (long long)(a) * (long long)(i + 1);
				costCounter += (long long)(b) * (long long)(i + 2);
#if DEBUG
				cout << "ADDING " << i + 1 << " PIPELINES" << endl;
				cout << "ADDING " << i + 2 << " PILLARS" << endl;
#endif
			} else {
				int pillarDist = i - lastPillar - 2;
#if DEBUG
				cout << "PILLARDIST " << pillarDist << endl;
#endif
				if(pillarDist >= goodToGoDownAt){
					costCounter += (long long)(b) * (long long)(pillarDist + 4);
					costCounter += (long long)(a) * (long long)(pillarDist + 4);
#if DEBUG
				cout << "ADDING " << pillarDist + 4 << " PIPELINES" << endl;
				cout << "ADDING " << pillarDist + 4 << " PILLARS" << endl;
#endif
				} else {
					costCounter += ((long long)(b) * 2LL + (long long)(a)) * (long long)(pillarDist + 2);
#if DEBUG
				cout << "ADDING " << pillarDist + 2 << " PIPELINES" << endl;
				cout << "ADDING " << 2 * (pillarDist + 2) << " PILLARS" << endl;
#endif
				}
			}
			lastPillar = i;
#if DEBUG
			cout << "COST COUNTER: " << costCounter << endl;
#endif
		}
	}
	if(lastPillar == -1){
		costCounter += (long long)(a) * n;
		costCounter += (long long)(b) * (n + 1);
#if DEBUG
		cout << "ADDING " << n << " PIPELINES" << endl;
		cout << "ADDING " << (n + 1) << " PILLARS" << endl;
#endif
	} else {
		costCounter += (long long)(a) * (n - lastPillar + 1);
		costCounter += (long long)(b) * (n - lastPillar + 1);
#if DEBUG
		cout << "ADDING " << (n - lastPillar + 1) << " PIPELINES" << endl;
		cout << "ADDING " << (n - lastPillar + 1) << " PILLARS" << endl;
#endif
	}
	cout << costCounter << endl;
}

int main(){
	int T;
	cin >> T;
	for(int i = 0; i < T; i++){
		doCase();
	}
	return 0;
}
