#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;

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

bool sortapple(applegroup a, applegroup b) {
	return (a.t < b.t);
}

bool sortcow(cowgroup a, cowgroup b) {
	return (a.t < b.t);
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
	sort(cows.begin(), cows.end(), sortcow);
	sort(apples.begin(), apples.end(), sortapple);
	// use earlier cows to match w/ earlier apples
	for (auto appleit = apples.begin(); appleit != apples.end(); appleit++) {
		for(auto cowit = cows.begin(); cowit != cows.end() && cowit->t <)
	}
	return 0;
}