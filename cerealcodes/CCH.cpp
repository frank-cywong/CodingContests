#include <iostream>
#include <set>
#include <cstring>
#include <unordered_map>

#define DEBUG 0

using namespace std;

int MOD = 1000000007;

set<int> cycLengths;

int startBoard[1000][1000];
int cycledBoard[1000][1000];
int tempBoard[1000][1000];
bool visited[1000001];
int startCoords[1000001];
int endCoords[1000001];

#define F first
#define S second
#define MAX 1000003
using namespace std;
 
typedef long long ll;
const int mod = 1000000007;
 
int prime[MAX];
unordered_map<int, int> max_map;
 
// Function to return a^n
int power(int a, int n)
{
    if (n == 0)
        return 1;
    int p = power(a, n / 2) % mod;
    p = (p * p) % mod;
    if (n & 1)
        p = (p * a) % mod;
    return p;
}
 
// Function to find the smallest prime factors
// of numbers upto MAX
void sieve()
{
    prime[0] = prime[1] = 1;
    for (int i = 2; i < MAX; i++) {
        if (prime[i] == 0) {
            for (int j = i * 2; j < MAX; j += i) {
                if (prime[j] == 0) {
                    prime[j] = i;
                }
            }
            prime[i] = i;
        }
    }
}
 
// Function to return the LCM modulo M
ll lcmModuloM(set<int> ar)
{
 
    for (auto its = ar.begin(); its != ar.end(); its++) {
        int num = *its;
        unordered_map<int, int> temp;
 
        // Temp stores mapping of prime factor to
        // its power for the current element
        while (num > 1) {
 
            // Factor is the smallest prime factor of num
            int factor = prime[num];
 
            // Increase count of factor in temp
            temp[factor]++;
 
            // Reduce num by its prime factor
            num /= factor;
        }
 
        for (auto it : temp) {
 
            // Store the highest power of every prime
            // found till now in a new map max_map
            max_map[it.first] = max(max_map[it.first], it.second);
        }
    }
 
    ll ans = 1;
 
    for (auto it : max_map) {
 
        // LCM is product of primes to their highest powers modulo M
        ans = (ans * power(it.F, it.S)) % mod;
    }
 
    return ans;
}


long long gcf(long long a, long long b){
	while(true){
		a %= b;
		if(a == 0){
			return b;
		}
		long long temp = a;
		a = b;
		b = temp;
	}
}

int main(){
	int n;
	cin >> n;
	int counter = 1;
	char temp;
	for(int i = 0; i < n; i++){
		for(int j = 0; j < n; j++){
			cin >> temp;
			if(temp == '.'){
				startBoard[i][j] = 0;
			} else {
				startBoard[i][j] = counter;
				counter++;
			}
		}
	}
	// move RIGHT
	for(int i = 0; i < n; i++){
		int j = 0;
		while(startBoard[i][j] != 0){
			j++;
		}
		int endIndex = n - 1;
		while(j > 0){
			j--;
			tempBoard[i][endIndex] = startBoard[i][j];
			endIndex--;
		}
	}
	// move UP
	for(int i = 0; i < n; i++){
		int j = n - 1;
		while(tempBoard[j][i] != 0){
			j--;
		}
		int endIndex = 0;
		while(j < n - 1){
			j++;
			cycledBoard[endIndex][i] = tempBoard[j][i];
			endIndex++;
		}
	}
	memset(tempBoard, 0, sizeof(int) * 1000 * 1000);
	// move LEFT
	for(int i = 0; i < n; i++){
		int j = n - 1;
		while(cycledBoard[i][j] != 0){
			j--;
		}
		int endIndex = 0;
		while(j < n - 1){
			j++;
			tempBoard[i][endIndex] = cycledBoard[i][j];
			endIndex++;
		}
	}
	memset(cycledBoard, 0, sizeof(int) * 1000 * 1000);
	// move DOWN
	for(int i = 0; i < n; i++){
		int j = 0;
		while(tempBoard[j][i] != 0){
			j++;
		}
		int endIndex = n - 1;
		while(j > 0){
			j--;
			cycledBoard[endIndex][i] = tempBoard[j][i];
			endIndex--;
		}
	}
	for(int i = 0; i < n; i++){
		for(int j = 0; j < n; j++){
			startCoords[startBoard[i][j]] = (i * 1000 + j);
			endCoords[cycledBoard[i][j]] = (i * 1000 + j);
		}
	}
#if DEBUG
	for(int i = 0; i < n; i++){
		for(int j = 0; j < n; j++){
			cout << cycledBoard[i][j] << " ";
		}
		cout << endl;
	}
#endif
	visited[0] = true;
	for(int i = 0; i < n; i++){
		for(int j = 0; j < n; j++){
			if(visited[startBoard[i][j]]){
				continue;
			}
			int cyc = 1;
			int startPos = 1000 * i + j;
			int curPos = endCoords[startBoard[i][j]];
			while(curPos != startPos){
				int curVal = startBoard[curPos / 1000][curPos % 1000];
				visited[curVal] = true;
				curPos = endCoords[curVal];
				cyc++;
			}
#if DEBUG
			cout << "CYC: " << cyc << endl;
#endif
			cycLengths.insert(cyc);
		}
	}
	sieve();
	cout << lcmModuloM(cycLengths) << endl;
}
