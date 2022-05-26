#include <iostream>
#include <string>
#include <stdlib.h>
#include <bitset>

int Move (std::string Args) {
	return 0;
}

int Clear (std::string Args) {
	return 0;
}

std::string Goto (std::string Args, std::string Instruction) {
	std::string InstructionParams = Args.substr(1,4);
	if (InstructionParams == "STOR") {
		Instruction = Instruction + "1";
	} else if (InstructionParams == "READ") {
		Instruction = Instruction + "0";
	} else {
		std::cout << "Error in instruction parameter 1: \"" << InstructionParams << "\" on line 1\nExiting...\n";
		exit(EXIT_FAILURE);
	}
	InstructionParams = Args.substr(5);
	Instruction = Instruction + std::bitset<3>(stoi(InstructionParams)).to_string();
	/*
	InstructionParams = Args.substr(6);
	if (InstructionParams == " ") {
		InstructionParams = Args.substr(5);
	} else {
		InstructionParams = Args.substr(5,6);
	}
	*/
	return Instruction;
}

int Declare (std::string Args) {
	return 0;
}

int main () {
	std::string Line;
	std::getline(std::cin, Line);
	//TODO create variable for substr instead of recalling function every time (also maybe use switch with pointers?
	if (Line.substr(0,4) == "GOTO") {
		std::cout << Goto(Line.substr(4,Line.length()), "00");
	} else if (Line.substr(0,4) == "MOVE") {
		std::cout << Move(Line.substr(5,Line.length()));
	} else if (Line.substr(0,4) == "CLER") {
		std::cout << Clear(Line.substr(5,Line.length()));
	} else if (Line.substr(0,4) == "DECL") {
		std::cout << Declare(Line.substr(5,Line.length()));
	} else {
		std::cout << "Error in instruction on line 1\nExiting...\n";
		exit(EXIT_FAILURE);
	}
}
