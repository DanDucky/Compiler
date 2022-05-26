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
	std::string LongSubstr;
	if (InstructionParams == "STOR") {
		Instruction = Instruction + "1";
	} else if (InstructionParams == "READ") {
		Instruction = Instruction + "0";
	} else {
		std::cout << "Error in instruction parameter 1: \"" << InstructionParams << "\" on line 1\nExiting...\n";
		exit(EXIT_FAILURE);
	}
	InstructionParams = Args.substr(5,1);
	Instruction = Instruction + std::bitset<3>(stoi(InstructionParams)).to_string();
	InstructionParams = Args.substr(8,1);
	if (InstructionParams == " ") {
		LongSubstr = Args.substr(9,3);
		InstructionParams = Args.substr(7,1);
	} else {
		LongSubstr = Args.substr(10,3);
		InstructionParams = Args.substr(7,2);
	}
	Instruction = Instruction + std::bitset<5>(stoi(InstructionParams)).to_string();
	if (LongSubstr == "ADD") {
		Instruction = Instruction + "0";
	} else if (LongSubstr == "CLR") {
		Instruction = Instruction + "1";
	} else {
		std::cout << "Error in GOTO instruction parameter at line 1, \"" << LongSubstr << "\"\nExiting...\n";
		exit(EXIT_FAILURE);
	}
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
		std::cout << Goto(Line.substr(4,Line.length()), "00") << "0000" << std::endl;
	} else if (Line.substr(0,4) == "MOVE") {
		std::cout << Move(Line.substr(5,Line.length())) << std::endl;
	} else if (Line.substr(0,4) == "CLER") {
		std::cout << Clear(Line.substr(5,Line.length())) << std::endl;
	} else if (Line.substr(0,4) == "DECL") {
		std::cout << Declare(Line.substr(5,Line.length())) << std::endl;
	} else {
		std::cout << "Error in instruction on line 1\nExiting...\n";
		exit(EXIT_FAILURE);
	}
}
