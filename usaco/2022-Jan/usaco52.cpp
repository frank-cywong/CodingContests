#include <iostream>
#include <vector>
#include <cstring>
#include <utility>
#include <unordered_set>

using namespace std;

int N;
int Q;

vector<unordered_set<int>> pathed;
bool isActive[100001];
bool visited[100001];
int mostRecentRelevant[100001];
vector<pair<int, int>> paths;

pair<unordered_set<int>, bool>* dfscheck(int i) {
	if (visited[i]) {
		unordered_set<int> empty;
		pair<unordered_set<int>, bool>* toreturn = new pair<unordered_set<int>, bool>;
		toreturn->first = empty;
		toreturn->second = false;
		return toreturn;
	}
	visited[i] = true;
	unordered_set<int> toreturn;
	toreturn.insert(i);
	bool anyactive = isActive[i];
	pair<unordered_set<int>, bool>* temp;
	for (auto it = pathed[i].begin(); it != pathed[i].end(); it++) {
		if (!visited[*it]) {
			temp = dfscheck(*it);
			if (temp->first.size() != 0) {
				toreturn.insert(temp->first.begin(), temp->first.end());
				anyactive |= temp->second;
			}
		}
	}
	pair<unordered_set<int>, bool>* returnval = new pair<unordered_set<int>, bool>;
	returnval->first = toreturn;
	returnval->second = anyactive;
	return returnval;
}

void recomp(int turn) {
	memset(visited, false, sizeof(bool) * (N+1));
	for (int i = 1; i <= N; i++) {
		if (!visited[i]) {
			pair<unordered_set<int>, bool>* visitedAndRelevant = dfscheck(i);
			if (visitedAndRelevant->first.size() == 0 || visitedAndRelevant->second == false) {
				continue;
			}
			for (auto it = visitedAndRelevant->first.begin(); it != visitedAndRelevant->first.end(); it++) {
				mostRecentRelevant[*it] = turn;
			}
		}
	}
}

int main() {
	cin >> N;
	cin >> Q;
	memset(isActive, true, sizeof(bool) * 100001);
	char tempc;
	int tempa, tempb;
	pathed.reserve(N + 1);
	for (int i = 0; i < N + 1; i++) {
		unordered_set<int> empty;
		pathed.push_back(empty);
	}
	for (int i = 1; i <= Q; i++) {
		cin >> tempc;
		if (tempc == 'D') {
			cin >> tempa;
			isActive[tempa] = false;
			recomp(i);
			continue;
		}
		if (tempc == 'A') {
			cin >> tempa;
			cin >> tempb;
			pathed[tempa].insert(tempb);
			pathed[tempb].insert(tempa);
			pair<int, int> path;
			path.first = tempa;
			path.second = tempb;
			paths.push_back(path);
			recomp(i);
			continue;
		}
		if (tempc == 'R') {
			cin >> tempa;
			pair<int, int> path = paths[tempa-1];
			pathed[path.first].erase(path.second);
			pathed[path.second].erase(path.first);
			recomp(i);
			continue;
		}
	}
	for (int i = 1; i <= N; i++) {
		cout << mostRecentRelevant[i] << endl;
	}
	return 0;
}