#ifndef DBR_UTF8_CORE_HPP
#define DBR_UTF8_CORE_HPP

#include <cstddef>

namespace dbr
{
	namespace utf8
	{
		using byte = char;

		static constexpr std::size_t npos = -1;

		// returns npos if valid.
		// otherwise, returns index of first invalid byte.
		bool valid(const byte* coded, std::size_t num = npos);

		// returns number of codepoints in the encoded sequence
		// assumes sequence is valid
		std::size_t strlen(const byte* coded);
	}
}

#endif
