#include "graph.h"
#include "display.h"
#include "util.h"
#include "algo.h"

#include <iostream>

using namespace std;


int main() {
	Graph<int> g;
	int one = g.insert(1);
	int two = g.insert(2);
	g.dbl_connect(one,two);
	g.print();

	auto s = system(NULL);
	system("echo system");
	system("ls");

	for (int i = 30; i < 38; i++) {
		for (int j = 40; j < 48; j++) {
			cout << ESC << i << ";" << j << "m#" << RESET << " ";
		}
		cout << endl;
	}

	Display d;
	d.print(0,0,1);
	
	for (int i = 0; i < 256; i++) {
		if (i % 4 == 0 && i) cout << endl;
		cout << i;
		print_string("^ ", 7, i);
		print_string(". ", 3, i);
		print_string("\" ", 2, i);
		print_string("_ ", 10, i);
		print_string("~ ", 4, i);
		cout << "\t";
	}
	cout << endl;
}



