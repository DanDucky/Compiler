#include "TextProcessing.hpp"

int main () {
	std::string Line;
	std::getline(std::cin, Line);
	//TODO create variable for substr instead of recalling function every time (also maybe use switch)
	if (Line.substr(0,4) == "GOTO") {
		std::cout << Goto(Line.substr(4,Line.length()), "10") << "0000" << std::endl;
	} else if (Line.substr(0,4) == "MOVE") {
		std::cout << Move(Line.substr(5,Line.length()), "00") << std::endl;
	} else if (Line.substr(0,4) == "CLER") {
		std::cout << Clear(Line.substr(5,Line.length()), "01") << std::endl;
	} else if (Line.substr(0,4) == "DECL") {
		std::cout << Declare(Line.substr(5,Line.length()), "11") << std::endl;
	} else {
		std::cout << "Error in instruction on line 1\nExiting...\n";
		exit(EXIT_FAILURE);
	}
}
