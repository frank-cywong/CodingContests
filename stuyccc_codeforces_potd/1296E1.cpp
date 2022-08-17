#include <iostream>
#include <algorithm>
#include <cstring>

using namespace std;

int main(){
	int n;
	char temp;
	char zeroLast = '`';
	char oneLast = '`';
	//char string[200];
	//char sorted[200];
	bool coloured[200];
	cin >> n;
	bool failed = false;
	for(int i = 0; i < n; i++){
		cin >> temp;
		if(!failed){
			//string[i] = temp;
			if(temp >= zeroLast){
				zeroLast = temp;
				coloured[i] = false;
				continue;
			}
			if(temp >= oneLast){
				oneLast = temp;
				coloured[i] = true;
				continue;
			}
			failed = true;
		}
		/*
		if(i == 0){
			coloured[i] = false;
			continue;
		}
		if(!failed){
			string[i] = temp;
			// this is inefficient but since n = 200 n^2logn is fine
			memcpy(sorted, string, sizeof(char) * (i + 1));
			sort(sorted, sorted + i);
			bool sameColor = coloured[j-1];
			for(int j = i; j >= 0; j--){ // also inefficient but fine
				if(sorted[j] == temp){ // found loc
				}
			}
		}
		*/
	}
	if(failed){
		cout << "NO" << endl;
		return 0;
	}
	cout << "YES" << endl;
	for(int i = 0; i < n; i++){
		cout << (coloured[i] ? 1 : 0);
	}
	return 0;
}
