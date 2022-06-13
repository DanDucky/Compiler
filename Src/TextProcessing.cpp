#include <iostream>
#include <string>
#include <stdlib.h>
#include <bitset>

std::string CacheMemoStorReader (std::string LongSubstr) {
	std::string StringOut;
	if (LongSubstr.substr(0,4) == "CACH") {
		StringOut = "00";
	} else if (LongSubstr.substr(0,4) == "MEMO") {
		StringOut = "01";
	} else if (LongSubstr.substr(0,4) == "STOR") {
		StringOut = "1" + std::bitset<2>(stoi(LongSubstr.substr(4,1))).to_string();
	} else {
		std::cout << "Error in instruction parameter 2: \"" << LongSubstr.substr(0,4) << "\" on line 1\nExiting...\n";
		exit(EXIT_FAILURE);
	}
	if ((std::stoi(LongSubstr.substr(4,2)) / 2) > 5 && StringOut.substr(0,1) == "0") {
		StringOut = StringOut +
				std::bitset<4>(std::stoi(LongSubstr.substr(4,2))).to_string() +
				"00";
	} else if ((std::stoi(LongSubstr.substr(4,2)) / 2) <= 5 && StringOut.substr(0,1) == "0") {
		StringOut = StringOut +
				std::bitset<4>(std::stoi(LongSubstr.substr(4,1))).to_string() +
				"00";
	} else if ((std::stoi(LongSubstr.substr(6,2)) / 2) > 5 && StringOut.substr(0,1) == "1") {
		StringOut = StringOut +
				std::bitset<5>(std::stoi(LongSubstr.substr(6,2))).to_string();
	} else if ((std::stoi(LongSubstr.substr(6,2)) / 2) <= 5 && StringOut.substr(0,1) == "1") {
		StringOut = StringOut +
				std::bitset<5>(std::stoi(LongSubstr.substr(6,1))).to_string();
	}
	return StringOut;
}

std::string CacheMemoReader (std::string LongSubstr) {
	if (LongSubstr.substr(0,4) == "CACH") {
		LongSubstr = "0";
	} else if (LongSubstr.substr(0,4) == "MEMO") {
		LongSubstr = "1";
	} else {
		std::cout << "Error in instruction parameter 2: \"" << LongSubstr.substr(0,4) << "\" on line 1\nExiting...\n";
		exit(EXIT_FAILURE);
	}
	return LongSubstr;
}

std::string Move (std::string Args, std::string Instruction) {
	std::string InstructionParams = Args.substr(0,4);
	std::string LongSubstr;
	if (InstructionParams == "STOR") {
		Instruction = Instruction + "11" + std::bitset<2>(std::stoi(Args.substr(4,1))).to_string();
	} else if (InstructionParams == "READ") {
		Instruction = Instruction + "10" + std::bitset<2>(std::stoi(Args.substr(4,1))).to_string();
	} else if (InstructionParams == "CACH") {
		Instruction = Instruction + "00";
	} else if (InstructionParams == "MEMO") {
		Instruction = Instruction + "01";
	} else {
		std::cout << "Error in instruction parameter 1: \"" << InstructionParams << "\" on line 1\nExiting...\n";
		exit(EXIT_FAILURE);
	}
	if (Instruction.substr(2,1) == "0" && Args.substr(5,1) == " ") {
		Instruction = Instruction +
				std::bitset<4>(std::stoi(Args.substr(4,1))).to_string() +
				CacheMemoStorReader(Args.substr(6,9));
	} else if (Instruction.substr(2,1) == "0" && Args.substr(5,1) != " ") {\
		Instruction = Instruction +
				std::bitset<4>(std::stoi(Args.substr(4,2))).to_string() +
				CacheMemoStorReader(Args.substr(7,10));
	}
	if (Args.substr(7,1) == " " && Instruction.substr(2,1) == "1") {
		Instruction = Instruction +
				std::bitset<5>(std::stoi(Args.substr(6,1))).to_string() +
				CacheMemoReader(Args.substr(8,4)) +
				std::bitset<4>(std::stoi(Args.substr(12,2))).to_string();
	} else if (Args.substr(7,1) != " " && Instruction.substr(2,1) == "1") {
		Instruction = Instruction +
				std::bitset<5>(std::stoi(Args.substr(6,2))).to_string() +
				CacheMemoReader(Args.substr(9,4)) +
				std::bitset<4>(std::stoi(Args.substr(12,2))).to_string();;
	} else if (Instruction.substr(2,1) == "1") {
		std::cout << "Error in instruction parameter after \"" << Args.substr(0,6) << "\" on line 1 while attempting to find storage line\nExiting...\n";
		exit(EXIT_FAILURE);
	}
	return Instruction;
}

std::string Clear (std::string Args, std::string Instruction) {
	std::string LongSubstr = Args.substr(0,4);
	if (LongSubstr == "CACH") {
		Instruction = Instruction + "11" +
				std::bitset<4>(std::stoi(Args.substr(4,2))).to_string() +
				"00000000"; // could probably fit 2 clears in 2 bytes :P
	} else if (LongSubstr == "MEMO") {
		Instruction = Instruction + "10" +
				std::bitset<4>(std::stoi(Args.substr(4,2))).to_string() +
				"00000000";
	} else if (LongSubstr == "STOR") {
		Instruction = Instruction + "0" +
				std::bitset<2>(std::stoi(Args.substr(4,1))).to_string() +
				std::bitset<5>(std::stoi(Args.substr(6,2))).to_string() +
				"000000";
	}
	return Instruction;
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
	Instruction = Instruction + std::bitset<3>(std::stoi(InstructionParams)).to_string();
	InstructionParams = Args.substr(8,1);
	if (InstructionParams == " ") {
		LongSubstr = Args.substr(9,3);
		InstructionParams = Args.substr(7,1);
	} else {
		LongSubstr = Args.substr(10,3);
		InstructionParams = Args.substr(7,2);
	}
	Instruction = Instruction + std::bitset<5>(std::stoi(InstructionParams)).to_string();
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

std::string Declare (std::string Args, std::string Instruction) {
	std::string SubInstruction = CacheMemoStorReader(Args);
	switch (std::stoi(SubInstruction.substr(0,1))) {
	case 1:
	Instruction = Instruction + SubInstruction;
	if (Args.substr(8,1) == " ") {
		Instruction = Instruction + std::bitset<6>(std::stoi(Args.substr(9,2))).to_string();
	} else if (Args.substr(8,1) != " ") {
		Instruction = Instruction + std::bitset<6>(std::stoi(Args.substr(8,2))).to_string();
	}
	break;
	case 0:
	Instruction = Instruction + SubInstruction.substr(0,6);
	if (Args.substr(6,1) == " ") {
		Instruction = Instruction + std::bitset<8>(std::stoi(Args.substr(7,2))).to_string();
	} else if (Args.substr(6,1) != " ") {
		Instruction = Instruction + std::bitset<8>(std::stoi(Args.substr(6,2))).to_string();
	}
	break;
	}
	return Instruction;
}

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
