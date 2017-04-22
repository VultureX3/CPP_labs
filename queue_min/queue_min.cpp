#include <stdio.h>
#include <fstream>
#include <iostream>
#include <vector>
#include <stack>
#include <queue>
#include <algorithm>

using namespace std;
stack<pair<int, int> >s1, s2;

int main()
{
	ifstream f1("queuemin.in");
	ofstream f2("queuemin.out");
	int m, n, el, el_top, el_min;
	char com;
	f1 >> m;
	for (int i = 0; i < m; i++) {
		f1 >> com;
		if (com == '-') {
			if (s2.empty())
				while (!s1.empty()) {
					el_top = s1.top().first;
					s1.pop();
					el_min = s2.empty() ? el_top : std::min(el_top, s2.top().second);
					s2.push(make_pair(el_top, el_min));
				}
			el = s2.top().first;
			s2.pop();
		}
		if (com == '+') {
			f1 >> n;
			el = s1.empty() ? n : std::min(n, s1.top().second);
			s1.push(make_pair(n, el));
		}
		if (com == '?') {
			if (s1.empty() || s2.empty()) 
				el = s1.empty() ? s2.top().second : s1.top().second;
			else el = std::min(s1.top().second, s2.top().second);
			f2 << el << '\n';
		}
	}
	f1.close();
	f2.close();
	system("pause");
	return 0;
}