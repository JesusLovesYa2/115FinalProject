#include "util.h"//For the matrix
#include <fstream>//To read in files
#include <iostream>//Let's us do outputs for tests
#include <string>//Makes it easier to read the file

/*
Symbols and meanings for the map
^=mountain, .=desert, "=forest, =plain(space), ~=water
*/
class Map {
	Matrix* grid;//I've been doing all this in the web editor, I'll test the code in a bit
	
public:
	Map(ifstream inputFile) {//Make a map from a input file
		//We have a decision to make, 1.Make the Map grow dynamicly while reading or 2. Make a bigger map than we need and fill it in as we go.
		inputFile.open("map1.txt", ifstream::in);
		if (!inFile.is_open()) {
			std::cout<<"File did not open, using a default matrix"<<std::endl;
			//TODO default matrix here with default value that will signal to read a newline if reached by the mapToGraph function, 
			//I'm thinking '!' is good.
			//Matrix(int nw, int nh, T v, int nm = 100), constructor for reference
			grid = new Matrix<char> (10, 10, '!');// 10 by 10 matrix filled with '!' by default. Default size is 100 but we can make it bigger
			//by adding a fourth value
		}
		std::string s;

		//Use these to to put each char in the right spot
		int xIndex = 0;
		int yIndex = 0;
		
		while (getline(inputFile,s)){//Read from file into s one line at a time until it can't
			for(char c : s){//Range based for loop that goes until s is done
				grid->set(xIndex,yIndex,c);
				xIndex++;//Move to the right
			}
			xIndex=0;//Back to the first column
			yIndex++;//Move down one row
		}
	}

	~Map() {
		delete grid;
	}

	int get_height() const {
		return grid->get_height();
	}

	int get_width() const {
		return grid->get_width();
	}

	char get(int x, int y) const {//Return value at x, y
		return grid->get(x, y);
	}

	bool set(int x, int y, char c) {//Set value at x, y
		return grid->set(x, y, c);
	}

	void print(bool n= false) {//Print all the values, the bool n changes the layout for printing and the results
		grid.print(n);			//(It looks to me that n true relies on individual arrays and n false just uses the matrix)
	}

	bool pop_c(int c) {
		//remove a column without moving others 
		return grid->pop_c();
	}
	bool pop_r(int r) {
		//remove a row without moving others 
		return grid->pop_r();
	}

	//Both find an empty row/column and fill in default values or make a new row/column if there is no empty space
	int add_c() {
		return grid->add_c();
	}
	int add_r() {
		return grid->add_r();
	}
};
