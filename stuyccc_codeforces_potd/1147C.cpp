#include <iostream>

using namespace std;

int main(){
	int piles[50];
	int n;
	cin >> n;
	int temp;
	int min = 51;
	for(int i = 0; i < n; i++){
		cin >> temp;
		piles[i] = temp;
		if(temp < min){
			min = temp;
		}
	}
	int counter = 0;
	for(int i = 0; i < n; i++){
		if(piles[i] == min){
			counter++;
			if(counter > n / 2){
				cout << "Bob" << endl;
				return 0;
			}
		}
	}
	cout << "Alice" << endl;
	return 0;
}