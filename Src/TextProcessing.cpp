#include <iostream>
#include <string>

int Move (std::string Args) {
	return 0;
}

int Clear (std::string Args) {
	return 0;
}

int Goto (std::string Args) {
	return 0;
}

int Declare (std::string Args) {
	return 0;
}

int main () {
	std::string Line;
	std::cin >> Line;
	if (Line.substr(0,4) == "GOTO") {
		std::cout << Goto(Line.substr(5,Line.length()));
	} else if (Line.substr(0,4) == "MOVE") {
		std::cout << Move(Line.substr(5,Line.length()));
	} else if (Line.substr(0,4) == "CLER") {
		std::cout << Clear(Line.substr(5,Line.length()));
	} else if (Line.substr(0,4) == "DECL") {
		std::cout << Declare(Line.substr(5,Line.length()));
	}
}
