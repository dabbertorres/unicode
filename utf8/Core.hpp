#ifndef DBR_UNICODE_UTF8_CORE_HPP
#define DBR_UNICODE_UTF8_CORE_HPP

#include <cstddef>
#include <cstdint>

#include <ostream>

#include "Unicode.hpp"

namespace dbr
{
	namespace unicode
	{
		namespace utf8
		{
			// simple variable-length character data-structure
			struct Char
			{
				const char* const data;
				std::size_t byteCount;
			};

			// returns the length (in bytes) of the unicode sequence starting at coded
			std::size_t sequenceLength(const char* coded);

			// returns the unicode value of the first sequence in coded (U+xxxxxx notation)
			// may throw InvalidEncoding()
			std::uint32_t decode(const char* coded);

			// returns the unicode value of the first sequence in coded (U+xxxxxx notation)
			// sets length to the number of bytes used in the sequence
			// may throw InvalidEncoding()
			std::uint32_t decode(const char* coded, std::size_t& length);

			// returns npos if valid.
			// otherwise, returns index of first invalid byte.
			// count is byte-length of coded
			std::size_t valid(const char* coded, std::size_t count = npos);

			// returns true if the code point at coded is a diacritic (to be combined with the previous non-diacritic code point)
			bool isDiacritic(const char* coded);

			// returns true if the unicode value (U+xxxxxx notation) is a diacritic
			bool isDiacritic(std::uint32_t value);

			// returns number of codepoints in the encoded sequence
			// assumes sequence is valid
			// count is byte-length of coded
			std::size_t codepointLength(const char* coded, std::size_t count = npos);

			// returns the number of characters (more or less: codepointLength() - <number of diacritics>)
			// count is byte-length of coded
			std::size_t characterLength(const char* coded, std::size_t count = npos);

			// finds the nth codepoint in coded, returning the byte offset from coded
			// returns npos if coded does not have n + 1 codepoints
			std::size_t findNthCodepoint(const char* coded, std::size_t nth);

			// finds the nth character in coded, returning the byte offset from coded
			// returns npos if coded does not have n + 1 characters
			std::size_t findNthCharacter(const char* coded, std::size_t nth);

			std::ostream& operator<<(std::ostream& os, const Char& ch);
		}
	}
}

#endif
