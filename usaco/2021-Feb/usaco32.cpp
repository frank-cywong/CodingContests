/*
ID: Chun Yeung Wong [frankcw]
TASK: stone_game
LANG: C++11
*/

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cstring>
#include <set>
#include <queue>
#include <iterator>

using namespace std;
bool freq[100001];
bool tempfreq[100001];
int countfreq[100001];
set<int> changedvalues;
int maxchangedvalue = 0;
int N;

int main() {
	cin >> N;
	memset(freq, 0, sizeof(freq));
	memset(countfreq, 0, sizeof(countfreq));
	int temp;
	bool temp2;
	bool success;
	int output = 0;
	for (int i = 1; i < (N+1); i++) {
		cin >> temp;
		freq[temp] = !(freq[temp]);
		changedvalues.insert(temp);
		countfreq[temp] ++;
		if (temp > maxchangedvalue) {
			maxchangedvalue = temp;
		}
	}
	for (auto it = changedvalues.begin(); it != changedvalues.end(); it++) {
		for (int s = 1; s <= *it; s++) {
			memcpy(tempfreq, freq, sizeof(freq));
			tempfreq[*it] = !(tempfreq[*it]);
			if ((*it - s) != 0) {
				tempfreq[(*it - s)] = !(tempfreq[*it - s]);
			}
			success = true;
			temp2 = false;
			for (int testpos = 1; testpos <= maxchangedvalue; testpos++) {
				if ((testpos / s) == 0) {
					continue;
				}
				if (testpos == 1 || (testpos % s) == 0) {
					if (temp2 == true) {
						success = false;
						break;
					}
					temp2 = false;
				}
				temp2 = temp2 ^ tempfreq[testpos];
			}
			if (temp2 == true) {
				success = false;
			}
			if (success) {
				output += countfreq[*it];
			}
		}
	}
	cout << output;
	return 0;
}

