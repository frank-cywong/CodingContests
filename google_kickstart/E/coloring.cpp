#include <iostream>
#include <cmath>

using namespace std;

void doCase(int c){
    int N;
    cin >> N;
    cout << "Case #" << c << ": " << (int)(ceil(N / 5.0)) << endl;
}

int main(){
    int T;
    cin >> T;
    for(int i = 0; i < T; i++){
        doCase(i+1);
    }
    return 0;
}
