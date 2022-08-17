#include <iostream>
#include <algorithm>

using namespace std;

int main(){
	int N;
	cin >> N;
	int backwards[51][3];
	int values[50];
	int temp;
	for(int i = 0; i < N; i++){
		cin >> temp;
		values[N - i - 1] = temp;
	}
	backwards[0][0] = 0;
	backwards[0][1] = 0;
	backwards[0][2] = 0;
	for(int i = 1; i <= N; i++){
		backwards[i][2] = values[i-1] + backwards[i-1][2];
		backwards[i][1] = max(backwards[i-1][1], backwards[i][2] - backwards[i-1][0]);
		backwards[i][0] = max(backwards[i-1][0], backwards[i][2] - backwards[i-1][1]);
	}
	cout << backwards[N][2] - backwards[N][1] << " " << backwards[N][1] << endl;
}
