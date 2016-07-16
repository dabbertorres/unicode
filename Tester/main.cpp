#include <iostream>
#include <string>

#include "utf8/ImmutableString.hpp"

using namespace dbr::unicode;

int main(int argc, char** argv)
{
	utf8::ImmutableString utf8Str(u8"Oh hello—, there!!");

	std::cout << utf8Str.codepointCount() << '\n';
	std::cout << utf8Str.charCount() << '\n';
	std::cout << utf8Str.memSize() << '\n';

	std::cout << utf8Str << '\n';

	auto sub = utf8Str.substr(3, 7);

	std::cout << sub << '\n';

	std::string narrowStr(utf8Str.data(), utf8Str.memSize());
	std::cout << narrowStr << '\n';

	auto utf88th = utf8Str[8];
	auto narrow8th = narrowStr[8];

	std::cout << "utf8: " << utf88th << '\n';
	std::cout << "narrow: " << narrow8th << '\n';

	return 0;
}
