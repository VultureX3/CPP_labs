#include <stdio.h>
#include <fstream>
#include <iostream>
#include <iomanip>

using namespace std;

int main() {
	ifstream f1("garland.in");
	ofstream f2("garland.out");
	int n;
	double a, left = 0, right, last;
	double mid, prev, cur, next;
	bool ground;
	f1 >> n >> a;
	right = a;
	while ((right - left) > 0.01 / (n - 1)) {
		mid = (left + right) / 2;
		prev = a;
		cur = mid;
		ground = cur >= 0;
		for (int i = 3; i <= n; i++) {
			next = 2 * cur - prev + 2;
			ground &= next >= 0;
			prev = cur;
			cur = next;
		}
		if (ground) { right = mid; last = cur; }
		else left = mid;
	}
	f2 << fixed << setprecision(2) << last;
	return 0;
}