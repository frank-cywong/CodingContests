#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <functional>
#include <climits>
#include <string>

#define DEBUG 1

using namespace std;

const int MOD = 1000000007;

typedef struct s_dat{
	char flip; // flip values on propagation?
	int minval;
	int maxval;
	int minindex;
	int maxindex;
	void m(){
		if(flip == 1){
			flip = 0;
		} else {
			flip = 1;
		}
	}
} dat;


struct SEGTREE{
	vector<dat> data; // let 1 be the top pos, then values from [1, 2N-1] are used
	int N; // array size
	dat identityval;
	function<dat(dat, dat)> opfunc; // operator, can be non-commutative but must be associative
	SEGTREE(int size, dat identity, function<dat(dat,dat)> operatorfunction){
		N = size;
		identityval = identity;
		opfunc = operatorfunction;
		data = vector<dat>(2*N, identityval);
	}
	/*
	void debugprint(){
		string s = "[";
		for(auto it = data.begin(); it != data.end(); it++){
			if(it != data.begin()){
				s += ", ";
			}
			s += to_string(*it);
		}
		cout << s << endl;
	}
	*/
	void update(int index, dat val){ // ONLY WORKS FOR SETTING AT FIRST
		index += N;
		data[index] = val;
		index /= 2;
		while(index > 0){
			data[index] = opfunc(data[2*index], data[2*index+1]);
			index /= 2;
		}
	}
	void rangeflip(int l, int r){
#if DEBUG
		cout << "RF: [" << l << ", " << r << "]" << endl;
#endif
		l += N;
		r += N;
#if DEBUG
		cout << "RFE: [" << l << ", " << r << "]" << endl;
#endif
		while(l <= r){
			if(l % 2 == 1){
				data[l].m();
#if DEBUG
				cout << "FLIPPED: " << l << endl;
#endif
				++l;
			}
			if(r % 2 == 0){
				data[r].m();
#if DEBUG
				cout << "FLIPPED: " << r << endl;
#endif
				--r;
			}
			l /= 2;
			r /= 2;
		}
	}
	dat query(int start, int end){
		dat leftopval = identityval;
		dat rightopval = identityval;
		start += N;
		end += N;
		while(start <= end){
			if(start % 2 == 1){
				leftopval = opfunc(leftopval, data[start]);
				start++;
			}
			if(end % 2 == 0){
				rightopval = opfunc(data[end], rightopval);
				end--;
			}
			start /= 2;
			end /= 2;
		}
		return(opfunc(leftopval, rightopval));
	}
};

dat propagate_query(dat a, dat b){
	// assume a <= b
	int lminval = a.minval;
	int lmaxval = a.maxval;
	int rminval = b.minval;
	int rmaxval = b.maxval;
	int lminindex = a.minindex;
	int lmaxindex = a.maxindex;
	int rminindex = b.minindex;
	int rmaxindex = b.maxindex;
	if(a.flip){
		lminval = (MOD - a.maxval);
		lmaxval = (MOD - a.minval);
		lminindex = a.maxindex;
		lmaxindex = a.minindex;
	}
	if(b.flip){
		rminval = (MOD - b.maxval);
		rmaxval = (MOD - b.minval);
		rminindex = b.maxindex;
		rmaxindex = b.minindex;
	}
	dat newdat;
	newdat.flip = 0;
	if(lminval <= rminval){
		newdat.minval = lminval;
		newdat.minindex = lminindex;
	} else {
		newdat.minval = rminval;
		newdat.minindex = rminindex;
	}
	if(lmaxval >= rmaxval){
		newdat.maxval = lmaxval;
		newdat.maxindex = lmaxindex;
	} else {
		newdat.maxval = rmaxval;
		newdat.maxindex = rmaxindex;
	}
	return newdat;
}

dat blank_dat(int x, int i){
	dat r;
	r.flip = 0;
	r.minval = x;
	r.maxval = x;
	r.minindex = i;
	r.maxindex = i;
	return r;
}

void debug_pdat(dat d){
#if DEBUG
	cout << "DEBUG: [f = " << (int)(d.flip) << ", mv = " << d.minval << ", maxv = " << d.maxval << ", mini = " << d.minindex << ", maxi = " << d.maxindex << "]" << endl;
#endif
}

int fpower(int N){
	int r = 1;
	while(N >= 1){
		N /= 2;
		r *= 2;
	}
	return r;
}

void doCase(int t){
	dat identitydat;
	identitydat.flip = 0;
	identitydat.minval = MOD;
	identitydat.maxval = 0;
	identitydat.minindex = -1;
	identitydat.maxindex = -1;
	int N;
	cin >> N;
	int segsize = fpower(N);
#if DEBUG
	cout << "SEGSIZE: " << segsize << endl;
#endif
	SEGTREE segtree(segsize, identitydat, &propagate_query);
	for(int i = 1; i <= N; ++i){
		int x;
		cin >> x;
		dat bd = blank_dat(x, i);
		segtree.update(i-1,bd);
	}
	dat qrsp = segtree.query(0, N-1);
	debug_pdat(qrsp);
	int Q;
	cin >> Q;
	long long tcount = 0;
	for(int i = 0; i < Q; ++i){
		int lQ, rQ;
		cin >> lQ >> rQ;
		segtree.rangeflip(lQ-1, rQ-1);
		dat qrsp = segtree.query(0, N-1);
		debug_pdat(qrsp);
		tcount += qrsp.maxindex;
	}
	cout << "Case #" << t << ": " << tcount << endl;
}

int main(){
	cout << setprecision(32);
	int T;
	cin >> T;
	for(int i = 1; i <= T; i++){
		doCase(i);
	}
	return 0;
}