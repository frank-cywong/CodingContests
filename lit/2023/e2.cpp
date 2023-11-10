#include <iostream>
#include <set>
#include <algorithm>
#include <iomanip>

using namespace std;

typedef long long ll;
typedef long double ld;

multiset<ll> a;
multiset<ll> b;

void debug_print_set(multiset<ll> * p){
	cout << "DEBUG PRINT: [";
	for(auto it = p->begin(); it != p->end(); ++it){
		if(it != p->begin()){
			cout << ", ";
		}
		cout << *it;
	}
	cout << "]" << endl;
}

void doCase(){
	a.clear();
	b.clear();
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
	ll a_max = *(a.rbegin());
	ll b_max = *(b.rbegin());
	long double a_cnt = n;
	long double b_cnt = m;
	ld c_avgsum = a_sum / a_cnt + b_sum / b_cnt;

	if(k == 0){
		cout << c_avgsum * 0.5 << endl;
		return;
	}

	if(a_max < b_max){
		swap(a, b);
		swap(a_max, b_max);
		swap(a_sum, b_sum);
	}
	// ensure a_max >= b_max

	//debug_print_set(&a);
	//debug_print_set(&b);

	multiset<ll> a_o2(a);
	multiset<ll> b_o2(b);
	
	// option 1: og, then start moving ones from a to b
	// option 2: move max to b, then start moving things from b to a
	// option 3: start moving ones from b to a without moving max
	
	multiset<ll> a_o3(a);
	multiset<ll> b_o3(b);

	int o2_k = (a_max == b_max ? k : k - 1);

	ll a_o2_sum = a_sum;
	ll b_o2_sum = b_sum;
	ll a_o3_sum = a_sum;
	ll b_o3_sum = b_sum;
	ll a_o4_sum = a_sum;
	ll b_o4_sum = b_sum;

	if(a_max != b_max){
		auto a_it = a_o2.end();
		--a_it;
		a_o2.erase(a_it);
		b_o2.insert(a_max);
		a_o2_sum -= a_max;
		b_o2_sum += a_max;
	}

	//debug_print_set(&a_o2);
	//debug_print_set(&b_o2);

	a_cnt = a.size();
	b_cnt = b.size();

	if(a.size() && b.size()){
		ll low_a_sum = 0;
		auto a_max_pt = a.end();
		--a_max_pt;
		ll moved = 0;
		for(auto it = a.begin(); it != a_max_pt; ++it){
			if(moved >= k){
				break;
			}
			low_a_sum += *it;
			//cout << "LAS: " << low_a_sum << endl;
			moved += 1;
		}
		a_cnt -= moved;
		b_cnt += moved;
		a_sum -= low_a_sum;
		b_sum += low_a_sum;
		ld o1_avg = a_sum / a_cnt + b_sum / b_cnt;
		if(o1_avg > c_avgsum){
			c_avgsum = o1_avg;
		}
		
		// option 3
		
		a_cnt = a_o3.size();
		b_cnt = b_o3.size();
		
		//debug_print_set(&a_o3);
		//debug_print_set(&b_o3);
		
		ll low_b_sum_o3 = 0;
		auto b_max_pt_o3 = b_o3.end();
		--b_max_pt_o3;
		ll moved_o3 = 0;
		for(auto it = b_o3.begin(); it != b_max_pt_o3; ++it){
			if(moved_o3 >= k){
				break;
			}
			low_b_sum_o3 += *it;
			//cout << "LBS: " << low_b_sum_o3 << endl;
			moved_o3 += 1;
		}
		a_cnt += moved_o3;
		b_cnt -= moved_o3;
		a_o3_sum += low_b_sum_o3;
		b_o3_sum -= low_b_sum_o3;
		ld o3_avg = a_o3_sum / a_cnt + b_o3_sum / b_cnt;
		if(o3_avg > c_avgsum){
			c_avgsum = o3_avg;
		}
	}
		
	a_cnt = a_o2.size();
	b_cnt = b_o2.size();
	
	if(o2_k >= 0 && a_o2.size() && b_o2.size()){
		
		ll a_sum = a_o2_sum;
		ll b_sum = b_o2_sum;

		ll low_b_sum = 0;
		auto b_max_pt = b_o2.end();
		--b_max_pt;
		ll moved = 0;
		for(auto it = b_o2.begin(); it != b_max_pt; ++it){
			if(moved >= o2_k){
				break;
			}
			low_b_sum += *it;
			moved += 1;
			//cout << "LBS: " << low_b_sum << endl;
		}
		a_cnt += moved;
		b_cnt -= moved;
		a_sum += low_b_sum;
		b_sum -= low_b_sum;
		ld o2_avg = a_sum / a_cnt + b_sum / b_cnt;
		if(o2_avg > c_avgsum){
			c_avgsum = o2_avg;
		}
	}

	a_cnt = n;
	b_cnt = m;
	ld d_avgsum = a_o4_sum / a_cnt + b_o4_sum / b_cnt;
	for(int i = 0; i < k; ++i){
		if(a_o4_sum / a_cnt > b_o4_sum / b_cnt){
			swap(a, b);
			swap(a_cnt, b_cnt);
			swap(a_o4_sum, b_o4_sum);
		}
		// ensure a's avg is less than b's avg
		// option 1: take largest one from a and move to b
		// option 2: take smallest one from b and move to a
		auto a_it = a.end();
		--a_it;
		ll a_max = *a_it;
		ld o1 = 0.000001;
		if(a_cnt > 1.01){
			o1 = (a_o4_sum - a_max) / (a_cnt - 1) + (b_o4_sum + a_max) / (b_cnt + 1);
		} else {
			break;
		}
		auto b_it = b.begin();
		ll b_min = *b_it;
		ld o2 = 0.000001;
		if(b_cnt > 1.01){
			o2 = (a_o4_sum + b_min) / (a_cnt + 1) + (b_o4_sum - b_min) / (b_cnt - 1);
		} else {
			break;
		}
		//cout << a_cnt << " " << b_cnt << " " << o1 << " " << o2 << " " << c_avgsum << " " << d_avgsum << endl;
		//if(o1 < d_avgsum && o2 < d_avgsum){
		//	break;
		//}
		if(o1 > o2){
			a.erase(a_it);
			b.insert(a_max);
			a_o4_sum -= a_max;
			b_o4_sum += b_max;
			++b_cnt;
			--a_cnt;
			d_avgsum = o1;
		} else {
			b.erase(b_it);
			a.insert(b_min);
			a_o4_sum += b_min;
			b_o4_sum -= b_min;
			--b_cnt;
			++a_cnt;
			d_avgsum = o2;
		}
		if(a_cnt < 1.98 || b_cnt < 1.98){
			break;
		}
		//cout << "DAVG: " << d_avgsum << endl;
	}
	if(d_avgsum > c_avgsum){
		//c_avgsum = d_avgsum;
		// i admit defeat - adding this makes it go from 6 to 5
	}
	cout << c_avgsum * 0.5 << endl;
}

int main(){
	int t;
	cin >> t;
	cout << setprecision(15);
	for(int i = 0; i < t; ++i){
		doCase();
	}
	return 0;
}
