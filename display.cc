#include "display.h"

using namespace std;

Display::Display(/*Map* mp*/) {
	//m = mp;
	//r = m->get_rows();
	//c = m->get_cols();
	int tr = system("tput lines");
	int tc = system("tput cols");
	cout << tr << " " << tc << endl;
}

Display::~Display() {
	//delete m;
}

std::ostream& operator<<(std::ostream& os, Color& c) {
	os << c.r << ";" << c.g << ";" << c.b;
	return os;
}

void Display::print(int r, int c, bool path) {
	//TODO - get output character from m 
	char ch = 'G';
	string s;
	s += ch;
	s += " ";

	//move cursor 
	//TODO - convert r and c into strings 
	//TODO - BUG - const char* can't be built like this 
	//				no idea how to get ints into system(), then 
	const char* cmd = "tput cup " + r + ' ' + c + '\000';
	cout << cmd << endl;
	system(cmd);
	//cout << "test" << endl;
	
	//decide colors 
	int fg = get_fg_color(ch);
	int bg = (path ? 52 : 0);

	//write output character 
	print_string(s,fg,bg);
	
	//TODO - return cursor to user 
}

void print_string(string s, int fg, int bg) {
	cout << ESC << "38;5;" << fg << ";48;5;" << bg << "m" << s << RESET;
}

int get_fg_color(char c) {
	int r = 39;
	if (c == '^') r = 7;
	else if (c == '.') r = 3;
	else if (c == '\"') r = 2;
	else if (c == '_') r = 10;
	else if (c == '~') r = 4;
	else {
		Array<char> a(4,0);
		a.push_back('M');
		a.push_back('B');
		a.push_back('F');
		a.push_back('G');
		if (a.find(c) != -1) r = 1;
	}
	return r;
}



