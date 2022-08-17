#include <iostream>
#include <cstring>

using namespace std;

bool spruce[252][500][500]; // layer, row (n), col (m)
int n,m;

bool is_spruce(int l, int row, int col){
	l--;
	return(spruce[l][row][col-1] && spruce[l][row][col] && spruce[l][row][col+1] && spruce[l][row-1][col]);
}

void do_case(){
	int counter = 0LL;
	memset(spruce, false, 500*500*251);
	cin >> n >> m;
	char temp;
	for(int i = 0; i < n; i++){
		for(int j = 0; j < m; j++){
			cin >> temp;
			if(temp == '*'){
				spruce[0][i][j] = true;
				counter++;
			}
		}
	}
	//cout << "COUNTER: " << counter << endl;
	for(int layer = 1; layer < 252; layer++){
		int new_spruce = 0;
		for(int row = layer; row < n; row++){
			for(int col = layer; col < (m - layer); col++){
				//cout << "TESTING: " << layer << ", " << row << ", " << col << endl;
				if(is_spruce(layer, row, col)){
					//cout << "WORKED" << endl;
					spruce[layer][row][col] = true;
					new_spruce++;
				}
			}
		}
		if(new_spruce == 0){
			break;
		}
		counter += new_spruce;
	}
	cout << counter << endl;
}

int main(){
	int t;
	cin >> t;
	for(int i = 0; i < t; i++){
		do_case();
	}
	return 0;
}
