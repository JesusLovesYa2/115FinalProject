#include "util.h"//For the matrix
#include <fstream>//To read in files

/*
^=mountain, .=desert, "=forest, =plain(space), ~=water
*/
class Map {
	Matrix<char> grid;//
	
public:
	Map(ifstream inputFile) {//Make a map from a input file
		
	}

	~Map() {
		//Since this isn't using any pointers and the Matrix should handle itself there is no need to delete anything
	}

	int get_height() const {
		return grid.get_height();
	}

	int get_width() const {
		return grid.get_width();
	}

	char get(int x, int y) const {//Return value at x, y
		return grid.get(x, y);
	}

	bool set(int x, int y, char c) {//Set value at x, y
		return grid.set(x, y, c);
	}

	void print(bool n= false) {//Print all the values, the bool n changes the layout for printing and the results
		grid.print(n);			//(It looks to me that n true relies on individual arrays and n false just uses the matrix)
	}

	bool pop_c(int c) {
		//remove a column without moving others 
		return grid.pop_c();
	}
	bool pop_r(int r) {
		//remove a row without moving others 
		return grid.pop_r();
	}

	//Both find an empty row/column and fill in default values or make a new row/column if there is no empty space
	int add_c() {
		return grid.add_c();
	}
	int add_r() {
		return grid.add_r();
	}
};
