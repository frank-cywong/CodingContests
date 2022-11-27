#include <bits/stdc++.h>

using namespace std;

int find_max_time_saved(vector<int> a, int aC, int maxA){
	if(aC <= 4){
		return 0;
	}
	int nMax = (int)(4 * sqrt((double)(aC)) + 7);
	if(nMax > maxA){
		nMax = maxA;
	}
	int tsMax = 0;
	for(int i = 2; i <= nMax; ++i){
		int tSum = 0;
		for(auto it = a.begin(); it != a.end(); it++){
			tSum += (*it)/i;
		}
		tSum *= (i - 1);
		tSum -= i;
		if(tSum > tsMax){
			tsMax = tSum;
		}
	}
	return tsMax;
}

/* Return the shortest time required to print a string given 1 copy operation */
int molasses(int n, char c[], int l[])
{
	vector<int> aL;
	vector<int> bL;
	vector<int> cL;
	int aCount = 0;
	int bCount = 0;
	int cCount = 0;
	int maxA = 0;
	int maxB = 0;
	int maxC = 0;
	char last = '\0';
	for(int i = 0; i < n; ++i){
		switch(c[i]){
			case 'a':
				if(last == 'a'){
					aL[aL.size() - 1] += l[i];
					aCount += l[i];
					if(aL[aL.size() - 1] > maxA){
						maxA = aL[aL.size() - 1];
					}
					break;
				}
				last = 'a';
				aL.push_back(l[i]);
				aCount += l[i];
				if(l[i] > maxA){
					maxA = l[i];
				}
				break;
			case 'b':
				if(last == 'b'){
					bL[bL.size() - 1] += l[i];
					bCount += l[i];
					if(bL[bL.size() - 1] > maxB){
						maxB = bL[bL.size() - 1];
					}
					break;
				}
				last = 'b';
				bL.push_back(l[i]);
				bCount += l[i];
				if(l[i] > maxB){
					maxB = l[i];
				}
				break;
			case 'c':
				if(last == 'c'){
					cL[cL.size() - 1] += l[i];
					cCount += l[i];
					if(cL[cL.size() - 1] > maxC){
						maxC = cL[cL.size() - 1];
					}
					break;
				}
				last = 'c';
				cL.push_back(l[i]);
				cCount += l[i];
				if(l[i] > maxC){
					maxC = l[i];
				}				
				break;
		}
	}
	int maxTS = find_max_time_saved(aL, aCount, maxA);
	if (maxTS < bCount){
		int bTS = find_max_time_saved(bL, bCount, maxB);
		if(bTS > maxTS){
			maxTS = bTS;
		}
	}
	if (maxTS < cCount){
		int cTS = find_max_time_saved(cL, cCount, maxC);
		if(cTS > maxTS){
			maxTS = cTS;
		}
	}
	return (aCount + bCount + cCount - maxTS);
}



int main()
{
	ios_base::sync_with_stdio(false); cin.tie(NULL);
    int T,n;
    cin >> T;
    while(T--)
    {
        cin >> n;
        char c[n];
        int l[n];
        for(int i = 0; i < n; i++) cin >> c[i];
        for(int i = 0; i < n; i++) cin >> l[i];
	    cout << molasses(n, c, l) << "\n";
    }
}
