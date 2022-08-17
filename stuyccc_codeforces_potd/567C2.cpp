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

vector<int> a;
unordered_map<int, int> occurencesL;
unordered_map<int, int> occurencesR;

int main(){
	int N, K;
	cin >> N >> K;
	int temp;
	for(int i = 0; i < N; i++){
		cin >> temp;
		//temp = 1;
		a.push_back(temp);
		if(occurencesR.find(temp) == occurencesR.end()){
			occurencesL[temp] = 0;
			occurencesR[temp] = 0;
		}
		occurencesR[temp]++;
	}
#if DEBUG
	cout << "INPUT END\n";
#endif
	long long sum = 0LL;
	for(int i = 0; i < N; i++){
		if(i != 0){
			occurencesL[a[i-1]]++;
		}
		occurencesR[a[i]]--;
		if(a[i] % K != 0){
			continue;
		}
		if(occurencesL.find(a[i] / K) == occurencesL.end()){
			continue;
		}
		long long prod = (long long)(a[i]) * (long long)(K);
		if(prod > 1000000000LL || prod < -1000000000LL){
			continue;
		}
		if(occurencesL.find(a[i] * K) == occurencesL.end()){
			continue;
		}
#if DEBUG
		cout << "i = " << i << " PASSED CHECKS\n";
#endif
		int lCount = occurencesL[a[i] / K];
		int rCount = occurencesR[a[i] * K];
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
