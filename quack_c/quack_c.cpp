#include <stdio.h>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <queue>
#define name first
#define strnum second

using namespace std;
const int mod = 65536;
vector<string>commands;
vector<int>registers(26);
vector<pair<string, int>>labels;
queue<int>quack;
int n = 0, l = 0;

int jump(string label) {
	for (int i = 0; i < l; i++)
		if (labels[i].name == label) return labels[i].strnum;
}

int main() {
	ifstream f1("quack.in");
	ofstream f2("quack.out");
	string com, label;
	int i = 0, a, b, x;
	bool run = true;
	char reg;
	while (getline(f1, com)) { commands.push_back(com); n++; }
	for (i = 0; i < n; i++)
		if (commands[i][0] == ':') {
			labels.push_back(make_pair(commands[i].substr(1), i));
			l++;
		}
	i = 0;
	while (i < n) {
		com = commands[i];
		switch (com[0]) {
		case (int)'+': {
			a = quack.front(); quack.pop();
			b = quack.front(); quack.pop();
			x = (a + b) & (mod - 1); quack.push(x);
			break;
		}
		case (int)'-': {
			a = quack.front(); quack.pop();
			b = quack.front(); quack.pop();
			x = (a - b) & (mod - 1); quack.push(x);
			break;
		}
		case (int)'*': {
			a = quack.front(); quack.pop();
			b = quack.front(); quack.pop();
			x = (a * b) & (mod - 1); quack.push(x);
			break;
		}
		case (int)'/': {
			a = quack.front(); quack.pop();
			b = quack.front(); quack.pop();
			if (b == 0) x = 0;
			else x = (a / b) & (mod - 1); quack.push(x);
			break;
		}
		case (int)'%': {
			a = quack.front(); quack.pop();
			b = quack.front(); quack.pop();
			if (b == 0) x = 0;
			else x = (a % b) & (mod - 1); quack.push(x);
			break;
		}
		case (int)'>': {
			reg = com[1];
			x = quack.front(); quack.pop();
			registers[(int)reg - (int) 'a'] = x;
			break;
		}
		case (int)'<': {
			reg = com[1];
			x = registers[(int)reg - (int) 'a'];
			quack.push(x);
			break;
		}
		case (int)'P': {
			if (com.length() == 1) {
				x = quack.front(); quack.pop();
			}
			else {
				reg = com[1];
				x = registers[(int)reg - (int) 'a'];
			}
			f2 << x << '\n';
			break;
		}
		case (int)'C': {
			if (com.length() == 1) {
				x = quack.front(); quack.pop();
			}
			else {
				reg = com[1];
				x = registers[(int)reg - (int) 'a'];
			}
			f2 << char(x % 256);
			break;
		}
		case (int)':': break;
		case (int)'J': {
			label = commands[i].substr(1);
			i = jump(label);
			break;
		}
		case (int)'Z': {
			reg = com[1];
			label = commands[i].substr(2);
			if (registers[(int)reg - (int) 'a'] == 0)
				i = jump(label);
			break;
		}
		case (int)'E': {
			label = commands[i].substr(3);
			if (registers[(int)com[1] - (int) 'a'] == registers[(int)com[2] - (int) 'a'])
				i = jump(label);
			break;
		}
		case (int)'G': {
			label = commands[i].substr(3);
			if (registers[(int)com[1] - (int) 'a'] > registers[(int)com[2] - (int) 'a'])
				i = jump(label);
			break;
		}
		case (int)'Q': {
			run = false;
			break;
		}
		default: {
			x = atoi(com.c_str());
			quack.push(x);
			break;
		}
		}
		i++;
		if (run == false) break;
	}
	f1.close();
	f2.close();
	system("pause");
	return 0;
}