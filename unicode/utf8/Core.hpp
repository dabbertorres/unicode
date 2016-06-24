#ifndef DBR_UNICODE_UTF8_CORE_HPP
#define DBR_UNICODE_UTF8_CORE_HPP

#include "Unicode.hpp"

namespace dbr
{
	namespace unicode
	{
		namespace utf8
		{
			// returns npos if valid.
			// otherwise, returns index of first invalid byte.
			bool valid(const byte* coded, std::size_t num = npos);

			// returns true if the code point at coded is a diacritic (to be combined with the previous non-diacritic code point)
			bool isDiacritic(const byte* coded);

			// returns number of codepoints in the encoded sequence
			// assumes sequence is valid
			std::size_t codepointLength(const byte* coded);

			// returns the number of characters (more or less: codepointLength() - <number of diacritics>)
			std::size_t characterLength(const byte* coded);
		}
	}
}

#endif
