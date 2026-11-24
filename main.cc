#include "graph.h"

#include <iostream>

using namespace std;

int main() {
	Graph<int> g;
	int one = g.insert(1);
	int two = g.insert(2);
	g.dbl_connect(one,two);
	g.print();
}




