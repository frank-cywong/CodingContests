#include <iostream>
#include <unordered_map>
#include <vector>

#define DEBUG 0

using namespace std;

#if DEBUG
void v_debug_print(vector<int> v){
	for(auto it = v.begin(); it != v.end(); it++){
		cout << *it << " ";
	}
	cout << "\n";
}
#endif

int b_search(vector<int> v, int cutoff){
#if DEBUG
	cout << "BSEARCH CALLED W/ CUTOFF: " << cutoff << endl;
	cout << v.size() << endl;
#endif
	if(v.size() == 1){
		return (v[0] < cutoff ? 1 : 0);
	}
	int front = 0;
	int back = v.size() - 1;
	if(v[back] < cutoff){
		return v.size();
	}
	if(v[back] == cutoff){
		return v.size() - 1;
	}
	if(v[front] >= cutoff){
		return 0;
	}
	while(back - front >= 2){
		int mid = (front + back) / 2;
#if DEBUG
		cout << "MID: " << mid << endl;
#endif
		if(v[mid] == cutoff){
			return mid; // eg. a[2] == cutoff, 2 elements less than cutoff
		}
		if(v[mid] < cutoff){
			front = mid;
		}
		if(v[mid] > cutoff){
			back = mid;
		}
	}
	if(v[front] == cutoff){
		return front;
	}
	return front + 1;
}

vector<int> a;
unordered_map<int, vector<int>*> occurences;

int main(){
	int N, K;
	cin >> N >> K;
	int temp;
	for(int i = 0; i < N; i++){
		cin >> temp;
#if DEBUG
		if(i % 10000 == 9999){
			cout << i << endl;
			cout << occurences.size() << endl;
			v_debug_print(*occurences[1]);
		}
#endif
		//temp = 1;
		a.push_back(temp);
		if(occurences.find(temp) == occurences.end()){
			vector<int>* v = new vector<int>;
			v->push_back(i);
			occurences[temp] = v;
			continue;
		}
		vector<int>* v = occurences[temp];
		v->push_back(i);
	}
#if DEBUG
	cout << "INPUT END\n";
#endif
	long long sum = 0LL;
	for(int i = 0; i < N; i++){
		if(a[i] % K != 0){
			continue;
		}
		if(occurences.find(a[i] / K) == occurences.end()){
			continue;
		}
		long long prod = (long long)(a[i]) * (long long)(K);
		if(prod > 1000000000LL || prod < -1000000000LL){
			continue;
		}
		if(occurences.find(a[i] * K) == occurences.end()){
			continue;
		}
#if DEBUG
		cout << "i = " << i << " PASSED CHECKS\n";
#endif
		vector<int> vLess = *occurences[(a[i] / K)];
		vector<int> vMore = *occurences[(a[i] * K)];
#if DEBUG
		v_debug_print(vLess);
		v_debug_print(vMore);
#endif
		int lCount = b_search(vLess, i);
		int rCount = vMore.size() - b_search(vMore, i + 1);
#if DEBUG
		cout << "LCOUNT: " << lCount << endl;
		cout << "RCOUNT: " << rCount << endl;
#endif
		sum += (long long)(lCount) * (long long)(rCount);
	}
#if DEBUG
	cout << "SUM:\n";
#endif
	cout << sum << endl;
	return 0;
}
