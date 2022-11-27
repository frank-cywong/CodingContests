#include <iostream>
#include <cmath>
#include <cstdlib>
#include <string>
#include <iomanip>

using namespace std;

typedef long double ld;

#define PI_LCL 3.1415926535897932384626433832L

ld doGuess(ld guessX, ld guessY){
	ld ret;
	cout << "P " << guessX << " " << guessY << endl;
	cin >> ret;
	return ret;
}

void doCase(){
	// step 1: find middle of segment between Steve and Alex
	// minimise function f(x, y) = d1 + d2
	// gradient descent with multiplier 15? for 300 cycles (900 P used)
	// don't stop if change value for both coords is < 0.0005
	// turns out this isn't middle of segment but rather altitude

	ld guessX = 0.0;
	ld guessY = 0.0;
	ld multiplier = 100.0;

	ld gX2;
	ld gY2;

	ld d;
	ld dx;
	ld dy;
	ld mx = 0.01;
	ld my = 0.01;
	ld mx2 = 0.0001;
	ld my2 = 0.0001;

	ld finDist;

	bool first = true;
	ld origDist;

	for(int cyc = 0; cyc < 250; cyc++){
		d = doGuess(guessX, guessY);
		gX2 = guessX * guessX;
		gY2 = guessY * guessY;
		d /= 2.0;
		d -= sqrtl(gX2 + gY2);
		if(first){
			origDist = d;
			//cout << "ORIG DIST: " << origDist << endl;
			first = false;
		}
		//cout << "d: " << d << endl;
		finDist = d;
		dx = doGuess(guessX + mx, guessY);
		dx /= 2.0;
		dx -= sqrtl(gX2 + 2.0 * mx * guessX + mx2 + gY2);
		//cout << "dx: " << dx << endl;
		dx -= d;
		dx /= mx;
		//cout << "dx val: " << dx << endl;
		dy = doGuess(guessX, (guessY + my));
		dy /= 2.0;
		dy -= sqrtl(gX2 + 2.0 * my * guessY + my2 + gY2);
		//cout << "dy: " << dy << endl;
		dy -= d;
		dy /= my;
		//cout << "dy val: " << dy << endl;
/*
		if(abs(dx * multiplier) < 0.0005 && abs(dy * multiplier) < 0.0005){
			break;
		}
*/
		guessX -= (dx * multiplier);
		guessY -= (dy * multiplier);
	}

/*
	// actual step 2: find location of (person in +x dir) via ternary search
	// consider function d(predicted pos) - d(actual pos)

	cout << "guessX: " << guessX << ", guessY: " << guessY << ", finDist: " << finDist << endl;

	ld slope = -(guessX / guessY);
	ld tX = finDist * (abs(guessY) / sqrtl(guessX * guessX + guessY * guessY));

	cout << "tx: " << tX << endl;

	ld lbound = 0;
	ld rbound = tX;

	ld a1;
	ld a2;

	for(int cyc = 0; cyc < 100; cyc++){
		cout << "lbound: " << lbound << ", rbound: " << rbound << endl;
		if(rbound - lbound < 0.001){
			break;
		}
		a1 = (lbound * 2.0 + rbound) / 3.0;
		a2 = (lbound + rbound * 2.0) / 3.0;
		ld x1a = guessX + a1;
		ld y1a = guessY + a1 * slope;
		ld x1b = guessX + a1 - tX;
		ld y1b = guessY + (a1 - tX) * slope;
		ld x2a = guessX + a2;
		ld y2a = guessY + a2 * slope;
		ld x2b = guessX + a2 - tX;
		ld y2b = guessY + (a2 - tX) * slope;
		ld dv1 = 0;
		dv1 += sqrtl(x1b * x1b + y1b * y1b);
		dv1 += sqrtl(x1a * x1a + y1a * y1a);
		dv1 -= origDist;
		ld dv2 = 0;
		dv2 += sqrtl(x2b * x2b + y2b * y2b);
		dv2 += sqrtl(x2a * x2a + y2a * y2a);
		dv2 -= origDist;
		if(dv2 > dv1){
			rbound = a2;
		} else {
			lbound = a1;
		}
	}

	ld loc_steveX = guessX + lbound;
	ld loc_steveY = guessY + lbound * slope;

	ld loc_alexX = guessX + (lbound - tX);
	ld loc_alexY = guessY + (lbound - tX) * slope;
*/

	//step 2: find angle of line via ternary search, allocate 100 cycles (200 P), stop when rangle - langle < 0.000002 (~ arcsin(1/500000))
	ld langle = 0.0;
	ld rangle = PI_LCL;

	ld mid;

	ld gx;
	ld gy;

	ld d1;
	ld d2;

	ld tinc = 5.0;

	for(int cyc = 0; cyc < 100; cyc++){
		if(rangle - langle < 0.000002){
			break;
		}
		ld a1 = langle + (rangle - langle) / 3.0;
		ld a2 = langle + (rangle - langle) * 2.0 / 3.0;
		gx = guessX + tinc * cosl(a1);
		gy = guessY + tinc * sinl(a1);
		d1 = doGuess(gx, gy);
		d1 /= 2.0;
		d1 -= sqrtl(gx * gx + gy * gy);
		gx = guessX + tinc * cosl(a2);
		gy = guessY + tinc * sinl(a2);
		d2 = doGuess(gx, gy);
		d2 /= 2.0;
		d2 -= sqrtl(gx * gx + gy * gy);
		if(d1 < d2){
			rangle = a2;
		} else {
			langle = a1;
		}
	}

	//cout << "slope of line: " << tanl(langle) << endl;

	ld slope = tanl(langle);

	ld tX = finDist / sqrtl(1.0 + slope * slope);

	//cout << "tx: " << tX << endl;

	ld lbound = 0;
	ld rbound = tX;

	ld a1;
	ld a2;

	for(int cyc = 0; cyc < 100; cyc++){
		//cout << "lbound: " << lbound << ", rbound: " << rbound << endl;
		if(rbound - lbound < 0.001){
			break;
		}
		a1 = (lbound * 2.0 + rbound) / 3.0;
		a2 = (lbound + rbound * 2.0) / 3.0;
		ld x1a = guessX + a1;
		ld y1a = guessY + a1 * slope;
		ld x1b = guessX + a1 - tX;
		ld y1b = guessY + (a1 - tX) * slope;
		ld x2a = guessX + a2;
		ld y2a = guessY + a2 * slope;
		ld x2b = guessX + a2 - tX;
		ld y2b = guessY + (a2 - tX) * slope;
		ld dv1 = 0;
		dv1 += sqrtl(x1b * x1b + y1b * y1b);
		dv1 += sqrtl(x1a * x1a + y1a * y1a);
		dv1 -= origDist;
		ld dv2 = 0;
		dv2 += sqrtl(x2b * x2b + y2b * y2b);
		dv2 += sqrtl(x2a * x2a + y2a * y2a);
		dv2 -= origDist;
		if(dv2 > dv1){
			rbound = a2;
		} else {
			lbound = a1;
		}
	}

	lbound = 0;
	for(int cyc = 0; cyc < 100; cyc++){
		//cout << "lbound: " << lbound << ", rbound: " << rbound << endl;
		if(rbound - lbound < 0.001){
			break;
		}
		ld mid = (lbound + rbound) / 2.0;
		ld x1a = guessX + mid;
		ld y1a = guessY + mid * slope;
		ld x1b = guessX + mid - tX;
		ld y1b = guessY + (mid - tX) * slope;
		ld dv1 = 0;
		dv1 += sqrtl(x1b * x1b + y1b * y1b);
		dv1 += sqrtl(x1a * x1a + y1a * y1a);
		dv1 -= origDist;
		if(dv1 < 0){
			rbound = mid;
		} else {
			lbound = mid;
		}
	}

	//cout << "origDist: " << origDist << endl;

	ld loc_steveX = guessX + lbound;
	ld loc_steveY = guessY + lbound * slope;

	ld loc_alexX = guessX + (lbound - tX);
	ld loc_alexY = guessY + (lbound - tX) * slope;

	cout << "B " << loc_steveX << " " << loc_steveY << " " << loc_alexX << " " << loc_alexY << endl;

/*
	ld correct_dx = rad * cosl(langle);
	ld correct_dy = rad * sinl(langle);

	ld loc_steveX = guessX + correct_dx;
	ld loc_steveY = guessY + correct_dy;

	ld loc_alexX = guessX - correct_dx;
	ld loc_alexY = guessY - correct_dy;

	cout << "B " << loc_steveX << " " << loc_steveY << " " << loc_alexX << " " << loc_alexY << endl;
*/

	string s;
	cin >> s;
	if(s == "WRONG_ANSWER"){
		exit(0);
	}

}

int main(){
	int T;
	cin >> T;
	cout << setprecision(20);
	for(int i = 0; i < T; ++i){
		doCase();
	}
	return 0;
}
