#include <iostream>

using namespace std;

void doCase(int t){
	int R, C;
	bool isEmpty = true;
	cin >> R >> C;
	char temp;
	for(int i = 0; i < R; i++){
		for(int j = 0; j < C; j++){
			cin >> temp;
			if(temp == '^'){
				isEmpty = false;
			}
		}
	}
	if(R == 1 || C == 1){
		if(isEmpty){
			cout << "Case #" << t << ": Possible\n";
			for(int i = 0; i < R; i++){
				for(int j = 0; j < C; j++){
					cout << ".";
				}
				cout << "\n";
			}
			return;
		} else {
			cout << "Case #" << t << ": Impossible\n";
			return;
		}
	}
	cout << "Case #" << t << ": Possible\n";
	for(int i = 0; i < R; i++){
		for(int j = 0; j < C; j++){
			cout << "^";
		}
		cout << "\n";
	}
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
