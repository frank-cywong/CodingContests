#include <iostream>
#include <vector>
#include <set>

using namespace std;

vector<bool> output;

bool basiccheck(vector<int> subcase) { // each case must be reducible by itself
	int last, cur;
	bool anythingchanged = true;
	while (anythingchanged) {
		anythingchanged = false;
		for (int j = 0; j < subcase.size(); j++) {
			if (j == 0) {
				last = subcase[j];
				continue;
			}
			cur = subcase[j];
			if (last == cur) { // we can simplify
				subcase.erase(subcase.begin() + j - 1, subcase.begin() + j + 1);
				j -= 2;
				anythingchanged = true;
			}
			last = cur;
		}
	}
	return(subcase.size() == 0);
}

vector<vector<int>> horizontalreduction(vector<vector<int>> testcase) { // reduces cases horizontally
	bool anythingreduced = true;
	int maxsize = 0;
	for (auto it = testcase.begin(); it != testcase.end(); it++) {
		if ((*it).size() > maxsize) {
			maxsize = (*it).size();
		}
	}
	while (anythingreduced) {
		anythingreduced = false;
		for (int j = 0; j < (maxsize - 1); j++) {
			int prevtoreduce = -1;
			set<int> toremove;
			for (int k = 0; k < testcase.size(); k++) {
				vector<int> subcase = testcase[k];
				if ((j + 1) >= (int)subcase.size()) {
					prevtoreduce = -1;
					continue;
				}
				if (subcase[j] != subcase[j + 1]) {
					continue;
				}
				if (prevtoreduce == -1) {
					prevtoreduce = subcase[j];
					continue;
				}
				if (subcase[j] == prevtoreduce) {
					toremove.insert(k - 1);
					toremove.insert(k);
					anythingreduced = true;
				}
			}
			if (toremove.size() != 0) {
				for (auto it = toremove.begin(); it != toremove.end(); it++) {
					testcase[*it].erase(testcase[*it].begin() + j, testcase[*it].begin() + j + 2);
				}
			}
		}
	}
	return testcase;
}

void process(vector<vector<int>> testcase, vector<long> coloursused) {
	for (int i = 0; i < coloursused.size(); i++) { // i is thing we are checking
		long uniquecolours = coloursused[i];
		for (int j = 0; j < coloursused.size(); j++) {
			if (i == j) {
				continue;
			}
			uniquecolours &= ~(coloursused[j]);
		}
		if (uniquecolours == 0) {
			continue;
		}
		vector<int> subcase = testcase[i];
		int last, cur;
		bool anythingchanged = true;
		while (anythingchanged) {
			anythingchanged = false;
			for (int j = 0; j < subcase.size(); j++) {
				if (j == 0) {
					last = subcase[j];
					continue;
				}
				cur = subcase[j];
				if (last == cur && ((uniquecolours & (1 << cur)) != 0)) { // we can simplify
					subcase.erase(subcase.begin()+j-1,subcase.begin()+j+1);
					j -= 2;
					anythingchanged = true;
				}
				last = cur;
			}
		}
		testcase[i] = subcase;
	}
	testcase = horizontalreduction(testcase);
	vector<int> prev;
	vector<int> cur;
	for (auto it = testcase.begin(); it != testcase.end(); it++) {
		if (!basiccheck(*it)) {
			output.push_back(false);
			return;
		}
		if (it == testcase.begin()) {
			prev = *it;
			continue;
		}
		cur = *it;
		if (cur != prev) {
			output.push_back(false);
			return;
		}
	}
	output.push_back(true);
	return;
}

int main() {
	int T;
	cin >> T;
	for (int tc = 0; tc < T; tc++) {
		int N, M;
		vector<vector<int>> testcase;
		vector<long> casecolours;
		cin >> N >> M;
		for (int lc = 0; lc < M; lc++) {
			vector<int> subcase;
			int ic, temp;
			long colours = 0;
			cin >> ic;
			for (int v = 0; v < ic; v++) {
				cin >> temp;
				subcase.push_back(temp);
				colours |= (1 << temp);
			}
			testcase.push_back(subcase);
			casecolours.push_back(colours);
		}
		process(testcase, casecolours);
	}
	for (int tc = 0; tc < T; tc++) {
		cout << (output[tc] ? "YES" : "NO") << endl;
	}
	return 0;
}