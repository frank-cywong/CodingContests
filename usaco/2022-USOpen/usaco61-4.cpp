#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;

#define norelax // try just not relaxing everything
//#undef norelax

struct applegroup {
	int t;
	int x;
	int n; // count
	int id; // unique id
	vector<int> matchingcows; // cows that can pick up this apple
	applegroup(int a, int b, int c, int d) {
		t = a;
		x = b;
		n = c;
		id = d;
		matchingcows = vector<int>();
	}
	bool isuseless() {
		return (n == 0 || optioncount == 0 || matchingcows.size() == 0);
	}
	int optioncount = 0;
};

struct cowgroup {
	int t;
	int x;
	int n;
	int id;
	vector<int> matchingapples; // apple groups that this cowgroup can pick up
	cowgroup(int a, int b, int c, int d) {
		t = a;
		x = b;
		n = c;
		id = d;
		matchingapples = vector<int>();
	}
	bool isuseless() {
		return (n == 0 || optioncount == 0 || matchingapples.size() == 0);
	}
	int optioncount = 0;
};

vector<applegroup> apples;
vector<cowgroup> cows;
vector<vector<int>> edges; // <appleid, cowid>

int adjust_onechoice() { // matches cows & apples with no other choices, returns paired up count if sth modified
	int returnval = 0;
	for (auto cowit = cows.begin(); cowit != cows.end(); cowit++) {
		cowgroup lclcow = *cowit;
		if (!lclcow.isuseless() && lclcow.optioncount == 1) {
			applegroup lclapple = apples[lclcow.matchingapples[0]];
			int tempi = 1;
			while (lclapple.isuseless()) {
				lclapple = apples[lclcow.matchingapples[tempi]];
				tempi++;
			}
			int toremove = min(lclcow.n, lclapple.n);
			cowit->n -= toremove;
			lclapple.n -= toremove;
			returnval += toremove;
			cowit->optioncount--;
			lclapple.optioncount--;
			apples[lclcow.matchingapples[tempi - 1]] = lclapple;
			// lclcow now useless:
			cowit->matchingapples.clear();
		}
	}
	for (auto appleit = apples.begin(); appleit != apples.end(); appleit++) {
		applegroup lclapple = *appleit;
		if (!lclapple.isuseless() && lclapple.optioncount == 1) {
			cowgroup lclcow = cows[lclapple.matchingcows[0]];
			int tempi = 1;
			while (lclcow.isuseless()) {
				lclcow = cows[lclapple.matchingcows[tempi]];
				tempi++;
			}
			int toremove = min(lclcow.n, lclapple.n);
			lclcow.n -= toremove;
			appleit->n -= toremove;
			returnval += toremove;
			lclcow.optioncount--;
			appleit->optioncount--;
			cows[lclapple.matchingcows[tempi - 1]] = lclcow;
			// lclapple now useless:
			appleit->matchingcows.clear();
		}
	}
	return returnval;
}

bool sortedges(vector<int> a, vector<int> b) {
	return(a[0] + a[1] > b[0] + b[1]);
}

int main() {
	int N;
	cin >> N;
	for (int i = 0; i < N; i++) {
		int q, t, x, n;
		cin >> q >> t >> x >> n;
		if (q == 1) {
			cowgroup cow = cowgroup(t, x, n, (int)cows.size());
			cows.push_back(cow);
		}
		else {
			applegroup apple = applegroup(t, x, n, (int)apples.size());
			apples.push_back(apple);
		}
	}
	// find matches
	for (auto cowit = cows.begin(); cowit != cows.end(); cowit++) {
		for (auto appleit = apples.begin(); appleit != apples.end(); appleit++) {
			applegroup lclapple = *appleit;
			cowgroup lclcow = *cowit;
			if (lclapple.t < lclcow.t) {
				break;
			}
			if (abs(lclcow.x - lclapple.x) <= abs(lclapple.t - lclcow.t)) { // cow can pick up apple
				cowit->matchingapples.push_back(lclapple.id);
				cowit->optioncount++;
				appleit->matchingcows.push_back(lclcow.id);
				appleit->optioncount++;
			}
		}
	}
	int output = 0;
#ifndef norelax
	while (true) { // if any cow can only pick up one apple, pick it up, and vice versa, repeatedly
		int temp = adjust_onechoice();
		if (temp == 0) {
			break;
		}
		output += temp;
	}
#endif
	bool anychanges = false;
	for (auto appleit = apples.begin(); appleit != apples.end(); appleit++) {
		appleit->optioncount = 0;
		appleit->matchingcows.clear();
	}
	for (auto cowit = cows.begin(); cowit != cows.end(); cowit++) {
		if (cowit->isuseless()) {
			continue;
		}
		cowit->optioncount = 0;
		cowit->matchingapples.clear();
		for (auto appleit = apples.begin(); appleit != apples.end(); appleit++) {
			applegroup lclapple = *appleit;
			cowgroup lclcow = *cowit;
			if (lclapple.t < lclcow.t) {
				break;
			}
			if (appleit->n == 0) {
				continue;
			}
			if (abs(lclcow.x - lclapple.x) <= abs(lclapple.t - lclcow.t)) { // cow can pick up apple
				cowit->matchingapples.push_back(lclapple.id);
				cowit->optioncount++;
				appleit->matchingcows.push_back(lclcow.id);
				appleit->optioncount++;
				anychanges = true;
				vector<int> tempv = vector<int>();
				tempv.push_back(lclapple.id);
				tempv.push_back(lclcow.id);
				edges.push_back(tempv);
			}
		}
	}
#ifndef norelax
	if (!anychanges) {
		cout << output; // for now, at least for sample case
		return 0;
	}
#endif
	sort(edges.begin(), edges.end(), sortedges);
	// edges is in dec order
	// prioritise edges with greater sum of apple and cow n count
	for (auto it = edges.begin(); it != edges.end(); it++) {
		applegroup lclapple = apples[it->at(0)];
		cowgroup lclcow = cows[it->at(1)];
		int toremove = min(lclcow.n, lclapple.n);
		lclcow.n -= toremove;
		lclapple.n -= toremove;
		output += toremove;
		lclcow.optioncount--;
		lclapple.optioncount--;
		apples[it->at(0)] = lclapple;
		cows[it->at(1)] = lclcow;
	}
	cout << output;
	return 0;
}