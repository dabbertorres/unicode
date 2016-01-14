#include <iostream>
#include <string>

#include "ImmString.hpp"

using namespace dbr;

int main(int argc, char** argv)
{
	utf8::imm::String utf8Str(u8"Oh hello—, there!!");

	std::cout << utf8Str.length() << '\n';
	std::cout << utf8Str.memSize() << '\n';

	std::cout << utf8Str.data() << '\n';

	std::string narrowStr(utf8Str.data(), utf8Str.memSize());
	std::cout << narrowStr << '\n';

	std::cout << "Hello, world!\n";
	return 0;
}