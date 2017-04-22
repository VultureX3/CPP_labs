#include <stdio.h>
#include <fstream>
#include <iostream>
#include <vector>

using namespace std;

const int len = 200000;
bool res = true;

int find_root(int* ptr, int n) {
	bool is_root[len];
	int i;
	for (i = 0; i < n; i++) {
		is_root[i] = true;
	}
	for (i = 0; i < n; i++) {
		if (*(ptr + i * 3 + 1) > 0) is_root[*(ptr + i * 3 + 1) - 1] = false;
		if (*(ptr + i * 3 + 2) > 0) is_root[*(ptr + i * 3 + 2) - 1] = false;
	}
	for (i = 0; i < n; i++) {
		if (is_root[i] == true) return i + 1;
	}
}

void check(int* ptr_tree, int* ptr_vert, int max, int min) {
	if ((*(ptr_vert) < min) || (*(ptr_vert) > max)) res = false;
	else {
		if (*(ptr_vert + 1) != 0) check(ptr_tree, ptr_tree + 3 * (*(ptr_vert + 1) - 1), *(ptr_vert) - 1, min);
		if (*(ptr_vert + 2) != 0) check(ptr_tree, ptr_tree + 3 * (*(ptr_vert + 2) - 1), max, *(ptr_vert) + 1);
	}
}

int main() {
	ifstream f1("check.in");
	ofstream f2("check.out");
	int i, n, min = INT_MIN, max = INT_MAX;
	int tree[len][3];
	int* ptr = &tree[0][0];
	f1 >> n;
	for (i = 0; i < n; i++) f1 >> tree[i][0] >> tree[i][1] >> tree[i][2];
	if (n > 0){
		int root = find_root(ptr, n);
		check(ptr, &tree[root - 1][0], max, min);
	}
	if (res == true) f2 << "YES";
	else f2 << "NO";
	system("pause");
	return 0;
}