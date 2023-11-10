#include <iostream>
#include <vector>
#include <iomanip>
#include <cassert>

using namespace std;

vector<int> primes;

bool isprime[1000001];

const int MAX_VAL = 1000000;

const int MOD = 1000000007;

#define DEBUG 0
#define DEBUGLIMIT 20

void gen_primes(){
	for(int i = 0; i <= MAX_VAL; ++i){
		if(i < 2){
			isprime[i] = false;
		} else {
			isprime[i] = true;
		}
	}
	for(int i = 2; i <= 1000; ++i){
		if(isprime[i]){
			for(int j = i * i; j <= MAX_VAL; j += i){
				isprime[j] = false;
			}
		}
	}
	for(int i = 2; i <= MAX_VAL; ++i){
		if(isprime[i]){
			primes.push_back(i);
		}
	}
}

// copied from https://www.geeksforgeeks.org/compute-ncrp-using-fermat-little-theorem/

/* Iterative Function to calculate (x^y)%p
in O(log y) */
unsigned long long power(unsigned long long x, 
                                  int y, int p)
{
    unsigned long long res = 1; // Initialize result
 
    x = x % p; // Update x if it is more than or
    // equal to p
 
    while (y > 0) 
    {
     
        // If y is odd, multiply x with result
        if (y & 1)
            res = (res * x) % p;
 
        // y must be even now
        y = y >> 1; // y = y/2
        x = (x * x) % p;
    }
    return res;
}
 
// Returns n^(-1) mod p
unsigned long long modInverse(unsigned long long n,  
                                            int p)
{
    return power(n, p - 2, p);
}
 
// Returns nCr % p using Fermat's little
// theorem.
unsigned long long nCrModPFermat(unsigned long long n,
                                 int r, int p)
{
    // If n<r, then nCr should return 0
    if (n < r)
        return 0;
    // Base case
    if (r == 0)
        return 1;
 
    // Fill factorial array so that we
    // can find all factorial of r, n
    // and n-r
    unsigned long long fac[n + 1];
    fac[0] = 1;
    for (int i = 1; i <= n; i++)
        fac[i] = (fac[i - 1] * i) % p;
 
    return (fac[n] * modInverse(fac[r], p) % p
            * modInverse(fac[n - r], p) % p)
           % p;
}

int H[1000000];
int multcount[1000001];
bool insequence[1000001];

int pcount[1000001];

void doCase(int ci){
	int N, K, D;
	cin >> N >> K >> D;
	for(int i = 0; i <= MAX_VAL; ++i){
		multcount[i] = 0;
		insequence[i] = false;
	}
	for(int i = 0; i < N; ++i){
		int temp;
		cin >> temp;
		H[i] = temp;
		insequence[temp] = true;
	}
	for(int i = 1; i <= MAX_VAL; ++i){
		for(int j = i; j <= MAX_VAL; j += i){
			if(insequence[j]){
				++multcount[i];
			}
		}
	}
#if DEBUG
	cout << "MULTCOUNT: [";
	for(int i = 1; i <= DEBUGLIMIT; i++){
		if(i != 1){
			cout << ", ";
		}
		cout << multcount[i];
	}
	cout << "]" << endl;
#endif
	for(int i = 1; i <= MAX_VAL; ++i){
		pcount[i] = nCrModPFermat(multcount[i], K, MOD);
	}
#if DEBUG
	cout << "PCOUNT: [";
	for(int i = 1; i <= DEBUGLIMIT; i++){
		if(i != 1){
			cout << ", ";
		}
		cout << pcount[i];
	}
	cout << "]" << endl;
#endif
	// exclude those above
	for(int i = MAX_VAL; i >= 1; --i){
		for(int j = i * 2; j <= MAX_VAL; j += i){
			pcount[i] -= pcount[j];
			if(pcount[i] < 0){
				pcount[i] += MOD;
			}
		}
	}
#if DEBUG
	cout << "PCOUNT AFTER CULL: [";
	for(int i = 1; i <= DEBUGLIMIT; i++){
		if(i != 1){
			cout << ", ";
		}
		cout << pcount[i];
	}
	cout << "]" << endl;
#endif
	// get all factors of D and sum:
	long long sum = 0LL;
	for(int i = 1; i <= D; ++i){
		if(D % i == 0){
			sum += pcount[i];
			sum %= MOD;
		}
	}
	// order does matter here!
	long long factModN = 1;
	for(long long i = 1; i <= K; ++i){
		factModN *= i;
		factModN %= MOD;
	}
	sum *= factModN;
	sum %= MOD;
	cout << "Case #" << ci << ": " << sum << endl;
}

int main(){
	cout << setprecision(32);
	gen_primes();
	int T;
	cin >> T;
	for(int i = 1; i <= T; i++){
		doCase(i);
	}
	return 0;
}