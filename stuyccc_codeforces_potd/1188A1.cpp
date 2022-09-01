#include <iostream>
#include <cstring>

using namespace std;

int EC[100001];

int main(){
	int n;
	cin >> n;
	int a, b;
	memset(EC, 0, sizeof(int) * 100001);
	for(int i = 0; i < (n - 1); i++){
		cin >> a >> b;
		EC[a]++;
		EC[b]++;
	}
	for(int i = 1; i <= n; i++){
		if(EC[i] == 2){
			cout << "NO";
			return 0;
		}
	}
	cout << "YES";
	return 0;
}
