#include <iostream>
#include <set>
#include <algorithm>
#include <cstring>
#include <vector>

using namespace std;

set<int> values;
vector<int> bSearchValues;
int occurs[1000001];
int val[100001];

void doCase(int c){
	values.clear();
	bSearchValues.clear();
	memset(occurs, 0, sizeof(int) * 1000001);
	memset(val, 0, sizeof(int) * 100001);
	int N, temp;
	cin >> N;
	for(int i = 0; i < N; i++){
		cin >> temp;
		values.insert(temp);
		occurs[temp]++;
		val[i] = temp;
	}
	for(auto it = values.begin(); it != values.end(); it++){
		bSearchValues.push_back(*it);
	}
	cout << "Case #" << c << ":";
	for(int i = 0; i < N; i++){
		int maxVal = 2 * val[i];
		auto it = upper_bound(bSearchValues.begin(), bSearchValues.end(), maxVal);
		it--;
		int found = *it;
		if(found == val[i] && occurs[val[i]] == 1){
			if(it == bSearchValues.begin()){
				found = -1;
			} else {
				it--;
				found = *it;
			}
		}
		cout << " " << found;
	}
	cout << "\n";
}

int main(){
	int T;
	cin >> T;
	for(int i = 0; i < T; i++){
		doCase(i + 1);
	}
	return 0;
}
