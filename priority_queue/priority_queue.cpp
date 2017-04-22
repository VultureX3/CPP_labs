#include <stdio.h>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#define num first
#define key second

using namespace std;
vector<pair<int, int> >heap (100010);
int heap_size = 0, oper = 0;

void min_heapify(int i) {
	int l = i * 2, r = i * 2 + 1, lw;
	if ((l <= heap_size) && (heap[l].key < heap[i].key)) lw = l;
	else lw = i;
	if ((r <= heap_size) && (heap[r].key < heap[lw].key)) lw = r;
	if (lw != i) {
		swap(heap[lw], heap[i]);
		min_heapify(lw);
	}
}

int heap_extract_min() {
	int m = heap[1].key;
	swap(heap[1], heap[heap_size]);
	heap_size--;
	min_heapify(1);
	return m;
}

void heap_decrease_key(int pos, int x) {
	heap[pos].key = x;
	while ((pos > 1) && (heap[pos / 2].key > heap[pos].key)) {
		swap(heap[pos], heap[pos / 2]);
		pos /= 2;
	}
}

void min_heap_insert(int x) {
	heap_size++;
	heap[heap_size] = make_pair(oper, INT_MAX);
	heap_decrease_key(heap_size, x);
}

int main()
{
	ifstream f1("priorityqueue.in");
	ofstream f2("priorityqueue.out");
	string com;
	int x, oper_num;
	heap[0] = make_pair(0, 0);
	while (f1 >> com) {
		oper++;
		if (com == "push") {
			f1 >> x;
			min_heap_insert(x);
		}
		if (com == "extract-min") {
			if (heap_size < 1) f2 << '*' << '\n';
			else f2 << heap_extract_min() << '\n';
		}
		if (com == "decrease-key") {
			f1 >> oper_num;
			f1 >> x;
			for (int i = 1; i <= heap_size; i++) 
				if (oper_num == heap[i].num) {
					heap_decrease_key(i, x);
					break;
				}
		}
	}
	f1.close();
	f2.close();
	system("pause");
	return 0;
}