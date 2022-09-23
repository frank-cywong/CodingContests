#include <iostream>
#include <set>

#define DEBUG 0

using namespace std;

typedef long long ll;

struct seed{
	ll count;
	ll day;
	ll value;
	ll uid;
};

bool orderByDay(seed a, seed b){
	return (a.day == b.day ? a.uid < b.uid : a.day < b.day);
}

bool orderByValue(seed a, seed b){
	return (a.value == b.value ? a.uid < b.uid : a.value > b.value);
}

set<seed, decltype(orderByValue)*> possibleSeeds(orderByValue);

set<seed, decltype(orderByDay)*> unusedSeeds(orderByDay);

ll consumeSeeds(ll toConsume){
#if DEBUG
	cout << "consuming " << toConsume << " seeds" << endl;
	cout << "setsize: " << possibleSeeds.size() << endl;
	for(auto it2 = possibleSeeds.begin(); it2 != possibleSeeds.end(); it2++){
		cout << it2->value << " " << it2->day << endl;
	}
#endif
	ll output = 0LL;
	for(auto it = possibleSeeds.begin(); it != possibleSeeds.end();){
		if(it->count > toConsume){
			output += (toConsume * it->value);
			seed newSeed;
			newSeed.count = (it->count - toConsume);
			newSeed.day = it->day;
			newSeed.value = it->value;
			newSeed.uid = it->uid;
			possibleSeeds.erase(possibleSeeds.begin());
			possibleSeeds.insert(possibleSeeds.begin(), newSeed);
			it = possibleSeeds.begin();
			break;
		}
		toConsume -= it->count;
		output += (it->count * it->value);
		possibleSeeds.erase(possibleSeeds.begin());
		it = possibleSeeds.begin();
	}
#if DEBUG
	cout << "output: " << output << endl;
	cout << "setsize: " << possibleSeeds.size() << endl;
#endif
	return output;
}

void doCase(int t){
	ll D, N, X;
	cin >> D >> N >> X;
	possibleSeeds.clear();
	unusedSeeds.clear();
	ll tQ, tL, tV;
	for(int i = 0; i < N; i++){
		cin >> tQ >> tL >> tV;
		seed tS;
		tS.count = tQ;
		tS.day = tL;
		tS.value = tV;
		tS.uid = i;
		unusedSeeds.insert(tS);
#if DEBUG
		cout << "Usetsize: " << unusedSeeds.size() << endl;
#endif
	}
	ll output = 0LL;
	ll pastDay = 1LL;
	ll curDay = 1LL;
	for(auto it = unusedSeeds.begin(); it != unusedSeeds.end();){
#if DEBUG
		cout << "Usetsize: " << unusedSeeds.size() << endl;
		for(auto it2 = unusedSeeds.begin(); it2 != unusedSeeds.end(); it2++){
			cout << it2->value << " " << it2->day << endl;
		}
#endif
		while(it != unusedSeeds.end() && it->day == curDay){
			possibleSeeds.insert(*it);
			unusedSeeds.erase(unusedSeeds.begin());
			it = unusedSeeds.begin();
		}
		pastDay = curDay;
		if(it != unusedSeeds.end()){
			curDay = it->day;
		} else {
			curDay = D;
		}
		#if DEBUG
				cout << "curDay: " << curDay << ", pastDay: " << pastDay << endl;
		#endif
		output += consumeSeeds((curDay - pastDay) * X);
	}
//	ll finDay = D;
#if DEBUG
//	cout << "fin: " << finDay << ", cur: " << curDay << endl;
#endif
//	output += consumeSeeds((finDay - curDay) * X);
	cout << "Case #" << t << ": " << output << endl;
}

int main(){
	int T;
	cin >> T;
	for(int i = 1; i <= T; i++){
		doCase(i);
	}
	return 0;
}
