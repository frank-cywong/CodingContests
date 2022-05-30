#include <iostream>
#include <vector>
#include <array>
#include <unordered_set>

using namespace std;

int T, N, K;

int process(vector<array<int, 2>> cows, unordered_set<int> paired) {
	if (paired.size() == cows.size()) {
		return 0;
	}
	int cownumber = 0;
	int firstunpaired = -1;
	auto it = cows.begin();
	for (it = cows.begin(); it != cows.end(); it++) {
		if (paired.find(cownumber) == paired.end()) {
			firstunpaired = cownumber;
			break;
		}
		cownumber++;
	}
	if (firstunpaired == -1) {
		return 0; // every single cow is paired
	}
	int optimal;
	if (T == 1) {
		optimal = INT_MAX;
	}
	else {
		optimal = INT_MIN;
	}
	bool existsunpairedinrange = false;
	int maxloc = cows[firstunpaired][0] + K;
	cownumber++;
	it++;
	while (true) {
		if (it == cows.end() || cownumber >= cows.size() || cows[cownumber][0] > maxloc) {
			if (existsunpairedinrange) {
				break;
			}
			else {
				optimal = cows[firstunpaired][1];
				break;
			}
		}
		if (paired.find(cownumber) == paired.end()) {
			existsunpairedinrange = true;
			unordered_set<int> temppaired(paired);
			temppaired.insert(firstunpaired);
			temppaired.insert(cownumber);
			int tempoptimal = process(cows, temppaired);
			if (T == 1 && tempoptimal < optimal) {
				optimal = tempoptimal;
			}
			if (T == 2 && tempoptimal > optimal) {
				optimal = tempoptimal;
			}
		}
		cownumber++;
	}
	return optimal;
	/*
	vector<int> bestpairing; // bestpairing represents the best pairing with item i not paired, might not be valid by itself, assumes item i is paired with sth else, so excl. value at i
	int bestvalidpairing = 0;
	int cownumber = 0;
	for (auto it = cows.begin(); it != cows.end(); it++) {
		array<int, 2> cow = *it;
		if (cownumber == 0) {
			bestvalidpairing = cow.at(1);
			bestpairing.push_back(bestvalidpairing);
			continue;
		}
		for (int i = 0; i < cownumber; i++) {
			if (cow.at(0) - K > cows.at(i).at(0)) {
				continue;
			}
			if (T == 1) {
				int tempbestvalidpairing = INT_MAX;
				if (bestpairing.at(i) < tempbestvalidpairing) {
					tempbestvalidpairing = bestpairing.at(i);
				}
			}
		}
		cownumber++;
	}
	*/
}

int main(){
	cin >> T >> N >> K;
	int temploc, tempweight, lastloc;
	lastloc = -1;
	int output = 0;
	array<int, 2> cowdata;
	vector<array<int, 2>> cowgroup;
	for (int i = 0; i < N; i++) {
		cin >> temploc >> tempweight;
		if (temploc > (lastloc + K) && lastloc != -1) { // cow group prior to this is independent
			output += process(cowgroup, unordered_set<int>());
			cowgroup.clear();
		}
		cowdata = {temploc, tempweight};
		cowgroup.push_back(cowdata);
		lastloc = temploc;
	}
	output += process(cowgroup, unordered_set<int>());
	cout << output;
	return 0;
}
