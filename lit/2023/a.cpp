#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct p{
	int a;
	int b;
};

bool p_sort(struct p a, struct p b){
	return (a.a < b.a);
}

vector<struct p> clubs;

int main(){
	int n;
	cin >> n;
	int twocount = 0;
	for(int i = 0; i < n; ++i){
		struct p temp;
		int tx, ty;
		cin >> tx >> ty;
		temp.a = tx;
		temp.b = ty;
		if(ty == 2){
			++twocount;
		}
		clubs.push_back(temp);
	}
	sort(clubs.begin(), clubs.end(), p_sort);
	int onecount = 0;
	// ones inclusively and to the left
	// twos inclusively and to the right
	int max = 0;
	for(auto it = clubs.begin(); it != clubs.end(); ++it){
		if(it->b == 1){
			++onecount;
		}
		int cmax = onecount + 2 * twocount;
		//cout << it->a << " " << it->b << "cmax: " << cmax << endl;
		if(it->b == 2){
			--twocount;
		}
		if(cmax > max){
			max = cmax;
		}
	}
	cout << max + 1000000000 << endl;
	return 0;
}
