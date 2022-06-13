#ifndef TEXTPROCESSING_HPP_
#define TEXTPROCESSING_HPP_
#include <iostream>
#include <string>
#include <stdlib.h>
#include <bitset>
std::string CacheMemoStorReader (std::string LongSubstr);
std::string CacheMemoReader (std::string LongSubstr);
std::string Move (std::string Args, std::string Instruction);
std::string Clear (std::string Args, std::string Instruction);
std::string Goto (std::string Args, std::string Instruction);
std::string Declare (std::string Args, std::string Instruction);
#endif /* TEXTPROCESSING_HPP_ */
