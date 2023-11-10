#include <iostream>
#include <set>
#include <algorithm>

using namespace std;

typedef long long ll;
typedef long double ld;

set<ll> a;
set<ll> b;

void doCase(){
	int n, m, k;
	cin >> n >> m >> k;
	ll a_sum = 0;
	ll b_sum = 0;
	for(int i = 0; i < n; ++i){
		ll temp;
		cin >> temp;
		a.insert(temp);
		a_sum += temp;
	}
	for(int i = 0; i < m; ++i){
		ll temp;
		cin >> temp;
		b.insert(temp);
		b_sum += temp;
	}
	//sort(a.begin(), a.end());
	//sort(b.begin(), b.end());
	long double a_cnt = n;
	long double b_cnt = m;
	ld c_avgsum = a_sum / a_cnt + b_sum / b_cnt;
	for(int i = 0; i < k; ++i){
		if(a_sum / a_cnt > b_sum / b_cnt){
			swap(a, b);
		}
		// ensure a's avg is less than b's avg
		// option 1: take largest one from a and move to b
		// option 2: take smallest one from b and move to a
		auto a_it = a.end();
		--a_it;
		ll a_max = *a_it;
		ld o1 = (a_sum - a_max) / (a_cnt - 1) + (b_sum + a_max) / (b_cnt + 1);
		auto b_it = b.begin();
		ll b_min = *b_it;
		ld o2 = (a_sum + b_min) / (a_cnt + 1) + (b_sum - b_min) / (b_cnt - 1);
		cout << o1 << " " << o2 << " " << c_avgsum << endl;
		if(o1 < c_avgsum && o2 < c_avgsum){
			break;
		}
		if(o1 > o2){
			a.erase(a_it);
			b.insert(a_max);
			c_avgsum = o1;
		} else {
			b.erase(b_it);
			a.insert(b_min);
			c_avgsum = o2;
		}
	}
	cout << c_avgsum * 0.5 << endl;
}

int main(){
	int t;
	cin >> t;
	for(int i = 0; i < t; ++i){
		doCase();
	}
	return 0;
}
