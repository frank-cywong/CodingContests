#include <iostream>
#include <cstring>

using namespace std;

int main(){
	int t;
	cin >> t;
	bool a[200000];
	for(int i = 0; i < t; i++){
		memset(a, 0, sizeof(bool) * 200000);
		int n;
		cin >> n;
		int temp;
		bool success = true;
		for(int j = 0; j < n; j++){
			cin >> temp;
			//int totest = remainder(temp + j, n);
			int totest = (temp + j) % n;
			if(totest < 0){
				totest += n;
			}
			//cout << "TOTEST: " << (temp + j) << " | " << n << " | " << totest << endl;
			if(a[totest]){
				success = false;
			}
			a[totest] = true;
		}
		if(success){
			cout << "YES" << endl;
		} else {
			cout << "NO" << endl;
		}
	}
	return 0;
}
