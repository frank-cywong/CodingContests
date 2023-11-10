#include <iostream>
#include <deque>

using namespace std;

deque<int> a;
deque<int> b;

void doCase(int t){
	int N, K;
	cin >> N >> K;
	cout << "Case #" << t << ": ";
	a = deque<int>();
	b = deque<int>();
	int temp;
	for(int i = 0; i < N; i++){
		cin >> temp;
		a.push_back(temp);
	}
	for(int j = 0; j < N; j++){
		cin >> temp;
		b.push_back(temp);
	}
	if(a == b){
		if(!(K == 1 || (N == 2 && K % 2 == 1))){
			cout << "YES\n";
			return;
		}
	}
	if(K == 0 || (N == 2 && K % 2 == 0)){
		cout << "NO\n";
		return;
	}
	for(int i = 0; i < N - 1; i++){
		int v = a.front();
		a.pop_front();
		a.push_back(v);
		if(a == b){
			cout << "YES\n";
			return;
		}
	}
	cout << "NO\n";
	return;
}

int main(){
	int T;
	cin >> T;
	for(int i = 1; i <= T; i++){
		doCase(i);
	}
	return 0;
}
