#include <iostream>
#include <cstring>
#include <vector>
#include <cmath>

using namespace std;

#define debug 1
#undef debug

bool output_case = false;

int ancestors[100001];
int lowbound[100001];
int highbound[100001];

int lowestupperbound[100001]; // gives the lowest value of the upper bound of all children of node i, including node i itself
int highestlowerbound[100001]; // gives the highest value of the lower bound of all children of node i, including node i itself

int imbalance[100001]; // imbalance when only considering node i and all its children
int maxval[100001]; // max value among node i and all its children
int minval[100001]; // min value among node i and all its children

vector<int> children[100001];

int values[100001]; // assigned si for all nodes i

void compbounds(int node) {
	vector<int> lclchildren = children[node];
	int templowestupperbound = highbound[node];
	int temphighestlowerbound = lowbound[node];
	for (auto it = lclchildren.begin(); it != lclchildren.end(); it++) {
		int curchild = *it;
		if (lowestupperbound[curchild] == -1) {
			compbounds(curchild);
		}
		if (lowestupperbound[curchild] < templowestupperbound) {
			templowestupperbound = lowestupperbound[curchild];
		}
		if (highestlowerbound[curchild] > temphighestlowerbound) {
			temphighestlowerbound = highestlowerbound[curchild];
		}
	}
	lowestupperbound[node] = templowestupperbound;
	highestlowerbound[node] = temphighestlowerbound;
}

void assignvalues(int node) {
	if (node == 1) {
		values[node] = (lowestupperbound[node] + highestlowerbound[node]) / 2;
		// that would be target, but clamp to lowbound / highbound
		if (values[node] < lowbound[node]) {
			values[node] = lowbound[node];
		}
		else if (values[node] > highbound[node]) {
			values[node] = highbound[node];
		}
	}
	else {
		int valancestornode = values[1]; // maybe try root node
		// assign val as close to root node as possible
		if (valancestornode < lowbound[node]) {
			values[node] = lowbound[node];
		}
		else if (valancestornode > highbound[node]) {
			values[node] = highbound[node];
		}
		else {
			values[node] = valancestornode;
		}
	}
	vector<int> lclchildren = children[node];
	for (auto it = lclchildren.begin(); it != lclchildren.end(); it++) { // dfs on children AFTER assigning values up top
		assignvalues(*it);
	}
}

void compimbalance(int node) {
	vector<int> lclchildren = children[node];
	maxval[node] = values[node];
	minval[node] = values[node];
	int tempimbalance = 0;
	for (auto it = lclchildren.begin(); it != lclchildren.end(); it++) {
		int childnode = *it;
		compimbalance(childnode);
		if (minval[childnode] < minval[node]) {
			minval[node] = minval[childnode];
		}
		if (maxval[childnode] > maxval[node]) {
			maxval[node] = maxval[childnode];
		}
		if (imbalance[childnode] > tempimbalance) {
			tempimbalance = imbalance[childnode];
		}
		if (abs(values[node] - minval[childnode]) > tempimbalance) {
			tempimbalance = abs(values[node] - minval[childnode]);
		}
		if (abs(values[node] - maxval[childnode]) > tempimbalance) {
			tempimbalance = abs(values[node] - maxval[childnode]);
		}
	}
	imbalance[node] = tempimbalance;
}

void do_case() {
	int N;
	cin >> N;
	memset(ancestors, 0, sizeof(int) * 100001);
	memset(lowbound, 0, sizeof(int) * 100001);
	memset(highbound, 0, sizeof(int) * 100001);
	memset(lowestupperbound, -1, sizeof(int) * 100001);
	memset(highestlowerbound, -1, sizeof(int) * 100001);
	memset(values, -1, sizeof(int) * 100001);
	for (int i = 1; i <= N; i++) {
		children[i] = vector<int>();
	}
	int temp;
	for (int i = 2; i <= N; i++) {
		cin >> temp;
		ancestors[i] = temp;
		children[temp].push_back(i);
	}
	int templ, temph;
	for (int i = 1; i <= N; i++) {
		cin >> templ >> temph;
		lowbound[i] = templ;
		highbound[i] = temph;
	}
	compbounds(1);
	if (true) {
		assignvalues(1);
	}
	compimbalance(1); // compute imbalance from values instead
#ifdef debug
	cout << "OUTPUT";
#endif
	cout << imbalance[1] << endl;
/*
	if (highestlowerbound[1] <= lowestupperbound[1]) {
#ifdef debug
		cout << "OUTPUT";
#endif
		cout << 0 << endl;
	}
	else {
#ifdef debug
		cout << "OUTPUT";
#endif
		cout << (highestlowerbound[1] - lowestupperbound[1] + 1) / 2 << endl;
	}
*/
	if (!output_case) {
		return;
	}
#ifdef debug
	cout << "OUTPUT";
#endif
	for (int i = 1; i <= N; i++) {
		cout << values[i];
		if (i != N) {
			cout << " ";
		}
	}
	cout << endl;
}

int main() {
	int T, B;
	cin >> T >> B;
	if (B) {
		output_case = true;
	}
	for (int i = 0; i < T; i++) {
		do_case();
	}
	return 0;
}