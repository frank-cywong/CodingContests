#include <iostream>
#include <string>

using namespace std;

void doCase(int c){
	int N;
	cin >> N;
	string s;
	cin >> s;
	bool worked = false;
	bool palin = false;
	for(int i = 1; i < s.length(); i++){
		if(s.length() % i != 0){
			continue;
		}
		int tl = s.length() + i;
		palin = false;
		for(int cmp = 0; cmp <= tl / 2; cmp++){
			int cI = tl - cmp - 1;
			if(cI < s.length() && s[cmp] != s[cI]){
				//cout << "total length: " << tl << ", value at: " << cmp << " not equal val at " << cI << endl;
				break;
			}
			if(cmp == tl / 2){
				palin = true;
			}
		}
		if(palin){
			cout << "Case #" << c << ": ";
			for(int j = i - 1; j >= 0; j--){
				cout << s[j];
			}
			cout << "\n";
			return;
		}
/*
		palin = false;
		for(int cmp = 0; cmp <= i / 2; cmp++){
			if(s[i] != s[i - cmp]){
				break;
			}
			if(cmp == i / 2){
				palin = true;
			}
		}
		if(!palin){
			continue;
		}
		worked = true;
		for(int k = 1; k < (s.length() / i); k++){
			for(int c = 0; c < i; c++){
				if(s[c + k * i] != s[c]){
					worked = false;
					break;
				}
			}
		}
		if(worked){
			cout << "Case #" << c << ": " << s.substr(0, i) << endl;
			return;
		}
*/
	}
	cout << "Case #" << c << ": " << s << endl;
	return;
}

int main(){
	int T;
	cin >> T;
	for(int i = 1; i <= T; i++){
		doCase(i);
	}
	return 0;
}
