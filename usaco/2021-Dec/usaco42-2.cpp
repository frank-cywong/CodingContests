#include <iostream>
#include <cstring>

using namespace std;

int N;
int output[200001];
void processinflection(int start, int end) {
	for (int i = start; i < end; i++) {
		output[i]++;
	}
}

int main() {
	cin >> N;
	int temp;
	int inflectionstart;
	int inflectionend;
	bool mode = true; // if true, find next maxima, if false, find next minima
	int last;
	for (int i = 0; i < N; i++) {
		cin >> temp;
		if (i == 0) {
			last = temp;
			continue;
		}
		if (mode) {
			if (temp < last) { // starting to decrease
				inflectionstart = last;
				mode = false;
			}
		}
		else {
			if (temp > last) { // starting to increase
				inflectionend = last;
				processinflection(inflectionend, inflectionstart);
				mode = true;
			}
		}
		if (i == (N - 1)) {
			if (!mode) {
				inflectionend = temp;
				processinflection(inflectionend, inflectionstart);
				break;
			}
		}
		last = temp;
	}
	for (int i = 0; i <= N; i++) {
		cout << output[i] << endl;
	}
	return 0;
}