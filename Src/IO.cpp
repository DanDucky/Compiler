#include "TextProcessing.hpp"
#include <fstream>
#include <chrono>
using namespace std::chrono;

std::string InstructionCall (std::string Line, int LineNum) {
	std::string Substr = Line.substr(0,4);
	std::string Instruction;
	if (Substr == "GOTO") {
		Instruction = Goto(Line.substr(4,Line.length()), "10") + "0000";
	} else if (Substr == "MOVE") {
		Instruction = Move(Line.substr(5,Line.length()), "00");
	} else if (Substr == "CLER") {
		Instruction = Clear(Line.substr(5,Line.length()), "01");
	} else if (Substr == "DECL") {
		Instruction = Declare(Line.substr(5,Line.length()), "11");
	} else {
		std::cout << "\033[1;31mError\033[0m in instruction on line " << LineNum << "\nExiting...\n";
		exit(EXIT_FAILURE);
	}
	return Instruction;
}
int main (int argc, char** argv) {
    std::ifstream Source;
    Source.open(argv[1]);
    std::string Line;
    int LineNum = 0;
    std::ofstream Binary("Out.dab");
    std::string LineOut;
    int ArrowLength;
    int Arrow = 0;
    if (Source.is_open()) {
    	while (std::getline (Source, Line)) {
    		auto start = high_resolution_clock::now();
    		LineNum++;
    		LineOut = InstructionCall(Line, LineNum);
    		Binary << LineOut << "\n";
    		std::cout << Line << " ";
    		ArrowLength = 22 - Line.length();
    		while (Arrow < ArrowLength) {
    			std::cout << "-";
    			Arrow++;
    		}
    		Arrow = 0;
    		auto stop = high_resolution_clock::now();
    		auto Duration = duration_cast<microseconds>(stop - start);
    		std::cout << "> " << LineOut << " | Line " << LineNum << " \033[1;32mcompleted\033[0m in " << Duration.count() << " microseconds \n";
    	}
    	std::cout << "Successfully wrote " << LineNum << " line(s) to Out.dab\n";
    } else {
    std::cout << "Error in opening source file, file does not exist\nExiting...\n";
    exit(EXIT_FAILURE);
    }
    Binary.close();
}
