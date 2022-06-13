#ifndef TEXTPROCESSING_HPP_
#define TEXTPROCESSING_HPP_
#include <iostream>
#include <string>
#include <stdlib.h>
#include <bitset>
std::string CacheMemoStorReader (std::string LongSubstr, int Line);
std::string CacheMemoReader (std::string LongSubstr, int Line);
std::string Move (std::string Args, std::string Instruction, int Line);
std::string Clear (std::string Args, std::string Instruction, int Line);
std::string Goto (std::string Args, std::string Instruction, int Line);
std::string Declare (std::string Args, std::string Instruction, int Line);
#endif /* TEXTPROCESSING_HPP_ */
