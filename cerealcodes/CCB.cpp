#include <iostream>

using namespace std;

long long permCount[19];

int main(){
	int n;
	cin >> n;
	permCount[1] = 0LL;
	permCount[2] = 1LL;
	for(int i = 2; i < n; i++){
		long long temp = permCount[i];
		temp *= (long long)(i);
		temp += (((long long)(i - 1)) * ((long long)(i - 1)));
		temp += 1LL;
		permCount[i+1] = temp;
	}
	cout << permCount[n] << endl;
	return 0;
}
