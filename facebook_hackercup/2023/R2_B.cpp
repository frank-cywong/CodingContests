#include <iostream>
#include <vector>
#include <iomanip>
#include <cassert>

using namespace std;

// want: - - - - [?] + + + +
int diff[2000000];

char check_offset(int offset_count, int N, bool flip){
	assert(offset_count < N);
	int new_left = offset_count;
	int new_right = offset_count - 1;
	bool flip_left_comp = 0;
	bool flip_right_comp = 1;
	if(flip){
		flip_left_comp = 1;
		flip_right_comp = 0;
	}
	int comps_needed = N / 2;
	// if odd: 5 / 2 -> 2; even: 4 / 2 -> 2
	for(int i = 0; i < comps_needed; ++i){
		if(new_right < 0){
			new_right += N;
			flip_right_comp = !flip_right_comp;
		}
		if(new_left >= N){
			new_left -= N;
			flip_left_comp = !flip_left_comp;
		}
		int left_val = diff[new_left];
		if(flip_left_comp){
			left_val = -left_val;
		}
		int right_val = diff[new_right];
		if(flip_right_comp){
			right_val = -right_val;
		}
		if(left_val >= 0 || right_val <= 0 || right_val != (-left_val)){
			return 0; // fail
		}
		++new_left;
		--new_right;
	}
	return 1;
}

void doCase(int ci){
	int N;
	cin >> N;
	char flipped = 0;
	for(int i = 0; i < N; ++i){
		int a;
		cin >> a;
		diff[i] = a;
	}
	for(int i = 0; i < N; ++i){
		int b;
		cin >> b;
		diff[i] -= b;
	}
	/*
	if(diff[N-1] < 0){
		for(int i = 0; i < N; ++i){
			diff[i] = -diff[i];
		}
		flipped = 1;
	}
	if(diff[N-1] == 0){
		// then check new "end"
		if(N % 2 == 0){
			cout << "Case #" << ci << ": -1" << endl;
			return;
		}
		// basically assert that we must have - [...] [...] 0 for parity to work out
		int nextdiffend = -diff[0];
		if(nextdiffend < 0){
			for(int i = 0; i < N; ++i){
				diff[i] = -diff[i];
			}
			flipped = 1;
		} else if (nextdiffend == 0){
			cout << "Case #" << ci << ": -1" << endl;
			return;
		}
	}
	*/
	int zc_count = 0;
	// index immediately preceding a zero crossing, define as - to [non-neg] or + to [non-plus]
	int zc1 = -1;
	int zc2 = -1;
	// zero diff, must be mid of odd seq
	int zd_count = 0;
	int zd1 = -1;
	int prev = diff[0];
	if(prev == 0){
		++zd_count;
		zd1 = 0;
		if(N % 2 == 0){
			cout << "Case #" << ci << ": -1" << endl;
			return;
		}
	}
	for(int i = 1; i < N; ++i){
		int cur = diff[i];
		if(cur == 0){
			if(zd_count == 1 || N % 2 == 0){
				cout << "Case #" << ci << ": -1" << endl;
				return;
			}
			++zd_count;
			zd1 = i;
		}
		if((prev < 0 && cur >= 0) || (prev > 0 && cur <= 0)){
			if(zc_count >= 2){
				cout << "Case #" << ci << ": -1" << endl;
				return;
			} else if (zc_count == 1){
				++zc_count;
				zc2 = i - 1;
			} else {
				++zc_count;
				zc1 = i - 1;
			}
		}
		prev = cur;
	}
	// case 1: zd present, only 1 case to check
	if(zd_count){
		int mid_pos = N / 2;
		int offset_count = zd1 - mid_pos;
		if(offset_count < 0){
			offset_count += N;
		}
		char res = check_offset(offset_count, N, false);
		if(res){
			cout << "Case #" << ci << ": " << offset_count << endl;
		} else {
			if(check_offset(offset_count, N, true)){
				cout << "Case #" << ci << ": " << offset_count + N << endl;
			} else {
				cout << "Case #" << ci << ": -1" << endl;
			}
		}
		return;
	}
	// ODD MUST HAVE 0 DIFF OTHERWISE MID WONT MATCH
	// A[N-(N+1)/2] = A[N/2+1/2] = B[N/2+1/2]
	if(N % 2 == 1){
		cout << "Case #" << ci << ": -1" << endl;
		return;
	}
	// case 2: no zd, zero zero-crossings
	// must make a zero-crossing through shift
	// eg. 2 2 2 2
	//     1 1 1 1
	// for even: only option is shift by N / 2
	if(zc_count == 0){
		int offset_count = N / 2;
		char res = check_offset(offset_count, N, false);
		if(res){
			cout << "Case #" << ci << ": " << offset_count << endl;
		} else {
			if(check_offset(offset_count, N, true)){
				cout << "Case #" << ci << ": " << offset_count + N << endl;
			} else {
				cout << "Case #" << ci << ": -1" << endl;
			}
		}
		return;
	}
	// case 3: 1 zero-crossing
	// zero-crossing must be put in the middle
	if(zc_count == 1){
		int mid_pos = N / 2 - 1; // eg. if N were 4, pos before mid would be 1
		int offset_count = zc1 - mid_pos;
		if(offset_count < 0){
			offset_count += N;
		}
		char res = check_offset(offset_count, N, false);
		if(res){
			cout << "Case #" << ci << ": " << offset_count << endl;
		} else {
			if(check_offset(offset_count, N, true)){
				cout << "Case #" << ci << ": " << offset_count + N << endl;
			} else {
				cout << "Case #" << ci << ": -1" << endl;
			}
		}
		return;
	}
	// case 4: 2 zero-crossings?
	// then end parity mismatch [+ + + - - - - +]?
	// [+ + - - - - + -] -> [+ - - - - + - -] -> not possible? perhaps?
	cout << "Case #" << ci << ": -1" << endl;
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