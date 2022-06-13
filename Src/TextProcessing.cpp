#include "TextProcessing.hpp"
// so much optimization I could do... so little importance...
std::string CacheMemoStorReader (std::string LongSubstr, int Line) {
	std::string StringOut;
	if (LongSubstr.substr(0,4) == "CACH") {
		StringOut = "00";
	} else if (LongSubstr.substr(0,4) == "MEMO") {
		StringOut = "01";
	} else if (LongSubstr.substr(0,4) == "STOR") {
		StringOut = "1" + std::bitset<2>(stoi(LongSubstr.substr(4,1))).to_string();
	} else {
		std::cout << "\033[1;31mError\033[0m in instruction parameter 2: \"" << LongSubstr.substr(0,4) << "\" on line " << Line << "\nExiting...\n";
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

std::string CacheMemoReader (std::string LongSubstr, int Line) {
	if (LongSubstr.substr(0,4) == "CACH") {
		LongSubstr = "0";
	} else if (LongSubstr.substr(0,4) == "MEMO") {
		LongSubstr = "1";
	} else {
		std::cout << "\033[1;31mError\033[0m in instruction parameter 2: \"" << LongSubstr.substr(0,4) << "\" on line " << Line << "\nExiting...\n";
		exit(EXIT_FAILURE);
	}
	return LongSubstr;
}

std::string Move (std::string Args, std::string Instruction, int Line) {
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
		std::cout << "\033[1;31mError\033[0m in instruction parameter 1: \"" << InstructionParams << "\" on line " << Line << "\nExiting...\n";
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
		std::cout << "\033[1;31mError\033[0m in instruction parameter after \"" << Args.substr(0,6) << "\" on line " << Line << " while attempting to find storage line\nExiting...\n";
		exit(EXIT_FAILURE);
	}
	return Instruction;
}

std::string Clear (std::string Args, std::string Instruction, int Line) {
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
	} else {
		std::cout << "\033[1;31mError\033[0m in instruction parameter 1: \"" << LongSubstr << "\" on line " << Line << "\nExiting...\n";
		exit(EXIT_FAILURE);
	}
	return Instruction;
}

std::string Goto (std::string Args, std::string Instruction, int Line) {
	std::string InstructionParams = Args.substr(1,4);
	std::string LongSubstr;
	if (InstructionParams == "STOR") {
		Instruction = Instruction + "1";
	} else if (InstructionParams == "READ") {
		Instruction = Instruction + "0";
	} else {
		std::cout << "\033[1;31mError\033[0m in instruction parameter 1: \"" << InstructionParams << "\" on line " << Line << "\nExiting...\n";
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
		std::cout << "\033[1;31mError\033[0m in GOTO instruction parameter at line " << Line << ", \"" << LongSubstr << "\"\nExiting...\n";
		exit(EXIT_FAILURE);
	}
	return Instruction;
}

std::string Declare (std::string Args, std::string Instruction, int Line) {
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
	default:
	std::cout << "\033[1;31mError\033[0m in instruction parameter 2 while trying to assign storage/memory/cache location on line " << Line << "\nExiting...\n";
	exit(EXIT_FAILURE);
	}
	return Instruction;
}
