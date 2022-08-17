#include <iostream>
#include <cmath>
#include <map>

using namespace std;

long long MAX_VAL = 1000000001;

map<long long, bool> winStates; // winStates[a * MAX_VAL + b] == does the person who plays first after that win

long long fastExp(long long a, int b){
	if(a == 1){
		return 1;
	}
	long long o = 1;
	while(b > 0){
		if(a > MAX_VAL){
			return (MAX_VAL);
		}
		if(b & 1){
			o *= a;
		}
		a = a * a;
		b >>= 1;
	}
	return o;
}

bool compWin(int a, int b, int n){
	long long checkIndex = MAX_VAL * (long long)(a) + (long long)(b);
	auto it = winStates.find(checkIndex);
	if(it != winStates.end()){
		return it->second;
	}
	bool isWin = false;
	if(fastExp(a, b) >= n){
		isWin = true;
	} else if(a < 3 && fastExp(3, b) >= n){
		int curTwoPow = fastExp(2, b);
		int incAmount = 0;
		while(curTwoPow < n){
			incAmount++;
			curTwoPow *= 2;
		}
		// if 1: incAmount odd, Stas wins, else Masha wins
		// eg. 1 4 17 -> 2 4 17 (Stas) -> 2 5 17 (Masha)
		// eg. 1 3 17 -> 1 4 17 (Stas) -> 2 4 17 (Masha) -> 2 5 17 (Stas)
		// if 2: flip these
		// eg. 2 3 17 -> 2 4 17 (Stas) -> 2 5 17 (Masha)
		if(incAmount % 2 == 0){
			isWin = false;
		} else {
			isWin = true;
		}
		if(a == 2){
			isWin = !isWin;
		}
	} else if (b == 1 && fastExp(a, 2) >= n){ // another edge case
		// can't increase to the square term
		// if (n-a) is even, (eg. 3 1 5), Stas wins, otherwise Masha wins
		isWin = ((n - a) % 2 == 0);
	} else if (b == 2 && fastExp(a, 3) >= n){
		// can't increase to the cube term
		int maxA = floor(pow(n - 0.1, 0.5));
		// eg. 4 2 36, maxA would be 5, Stas wins, otherwise Masha wins
		isWin = ((maxA - a) % 2 == 1);
	} else {
		isWin = !(compWin(a + 1, b, n) && compWin(a, b+1, n));
	}
	winStates.insert({checkIndex, isWin});
	return isWin;
}

int main(){
	int a, b, n;
	cin >> a >> b >> n;
	// special case: a = 1, and 3^b >= n whoever can switch it to 2 right before wins
	if(a == 1){
		int curTwoPow = fastExp(2, b);
		int incAmount = 0;
		if(curTwoPow >= n){
			cout << "Missing" << endl;
			return 0;
		}
	}
	bool win = compWin(a, b, n);
	cout << (win ? "Masha" : "Stas") << endl;
}
