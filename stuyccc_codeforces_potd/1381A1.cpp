#include <iostream>
#include <cstring>
#include <vector>

using namespace std;

void prefixflip(bool *bstring, int index){
	bool *end = bstring + index;
	while(bstring < end){
		//cout << "SWAPPING " << bstring << "|" << end;
		bool temp = !(*end);
		*end = !(*bstring);
		*bstring = temp;
		bstring++;
		end--;
	}
	if(bstring == end){
		*bstring = !(*bstring);
	}
}

void readbstring(bool *bstring, int n){
	char temp;
	for(int i = 0; i < n; i++){
		cin >> temp;
		if(temp == '1'){
			*bstring = true;
		}
		bstring++;
	}
}

/*
void debugprintbstring(bool *bstring, int n){
	cout << "DEBUGPRINT ";
	for(int i = 0; i < n; i++){
		cout << *bstring << " ";
		bstring++;
	}
	cout << endl;
}
*/

int main(){
	int t;
	cin >> t;
	bool bstring[1000];
	bool bstringtarget[1000];
	vector<int> output;
	for(int i = 0; i < t; i++){
		memset(bstring, false, sizeof(bool) * 1000);
		memset(bstringtarget, false, sizeof(bool) * 1000);
		output.clear();
		int n;
		cin >> n;
		int curindex = n - 1;
		readbstring(bstring, n);
		readbstring(bstringtarget, n);
		//debugprintbstring(bstring, n);
		//debugprintbstring(bstringtarget, n);
		while(curindex >= 0){
			//cout << curindex << endl;
			//debugprintbstring(bstring, n);
			if(bstring[curindex] != bstringtarget[curindex]){
				if(bstring[curindex] != bstring[0]){
					bstring[0] = !bstring[0];
					output.push_back(1);
				}
				//debugprintbstring(bstring, n);
				prefixflip(bstring, curindex);
				output.push_back(curindex + 1);
			}
			//debugprintbstring(bstring, n);
			curindex--;
		}
		//debugprintbstring(bstring, n);
		cout << output.size();
		for(auto it = output.begin(); it != output.end(); it++){
			cout << " " << *it;
		}
		cout << endl;
	}
	return 0;
}
