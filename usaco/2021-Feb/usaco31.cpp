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

int N;

multiset<int> values;

bool guaranteewin(int c, multiset<int> currentvalues) {
	if (currentvalues.size() == 0) {
		return false;
	}
	auto enditerator = currentvalues.end();
	enditerator--;
	int maxvalue = *enditerator;
	if (c > maxvalue) {
		return false;
	}
	if (currentvalues.size() == 1) {
		return true;
	}
/*
	auto seconditerator = enditerator;
	seconditerator--;
	if (((maxvalue / c) > ((*seconditerator) / c))) {
		return true;
	}
*/
	if (c != 1) {
		multiset<int> flattened;
		for (auto it = currentvalues.begin(); it != currentvalues.end(); it++) {
			if (*it < c) {
				continue;
			}
			flattened.insert((*it / c));
		}
		return (guaranteewin(1, flattened));
	}
	auto itmaxnumber = currentvalues.equal_range(maxvalue);
	int maxnumberappeartimes = distance(itmaxnumber.first, itmaxnumber.second);
	if ((maxnumberappeartimes % 2) == 1) {
		return true;
	}
	multiset<int> torun;
	torun = currentvalues;
	torun.erase(maxvalue);
	if (torun.size() == 0) {
		return false;
	}
	return(guaranteewin(1, torun));
/*
	int prev = 0;
	int cur;
	multiset<int> totest;
	for (auto it = currentvalues.begin(); it != currentvalues.end(); it++) {
		cur = *it;
		if (cur == prev) {
			continue;
		}
		prev = cur;
		for (int i = 1; i < cur; i++) {
			totest = currentvalues;
			totest.erase(*it);
			auto itpair = currentvalues.equal_range(*it);
			int dist = distance(itpair.first, itpair.second);
			for (int i = 1; i < dist; i++) {
				totest.insert(*it);
			}
			if ((*it - 1) != 0) {
				totest.insert((*it - i));
			}
			if (guaranteewin(1, totest)) {
				return false;
			}
		}
	}
	return true;
*/
}

int main() {
	cin >> N;
	int temp;
	for (int i = 0; i < N; i++) {
		cin >> temp;
		values.insert(temp);
	}
	int output = 0;
	auto enditerator = values.end();
	enditerator--;
	int maxvalue = *(enditerator);
	int prev = 0;
	int cur;
	multiset<int> totest;
	for (auto todelfrom = values.begin(); todelfrom != values.end(); todelfrom++) {
		cur = *todelfrom;
		if (cur == prev) {
			continue;
		}
		prev = cur;
		for (int todel = 1; todel <= cur; todel++) {
			auto itpair = values.equal_range(cur);
			int multiplier = distance(itpair.first, itpair.second);
			totest = values;
			totest.erase(cur);
			for (int i = 1; i < multiplier; i++) {
				totest.insert(cur);
			}
			if ((cur - todel) != 0) {
				totest.insert(cur - todel);
			}
			bool works = !(guaranteewin(todel, totest));
			if (works) {
				output += multiplier;
			}
		}
	}
	cout << output;
	return 0;
}

