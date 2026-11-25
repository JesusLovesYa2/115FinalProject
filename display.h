#ifndef H_DISPLAY 
#define H_DISPLAY 

#include "colors.h"
#include "graph.h"
#include "map.h"

#include <iostream>
#include <string>

//Definitions 
#define ESC "\033[" 
#define RESET "\033[m" 

void print_string(string s, int fg, int bg);
int get_fg_color(char c);

struct Color {
	int r;
	int g;
	int b;

	Color(int x, int y, int z) {
		r = x;
		g = y;
		b = z;
	}
};

std::ostream& operator<<(std::ostream& os, Color& c);

class Display {
	//Map* m;//TODO - update to match final class name and constructor 
	int sr;//screen rows 
	int sc;//screen columns 
	int r;//needed rows (from Map) 
	int c;//needed columns (from Map) 

	public:
	Display();
	//Display(Map* mp);
	~Display();

	void print(int r, int c, bool path = false);

	string bg_color(int c);
	string fg_color(int c);
};


#endif 


