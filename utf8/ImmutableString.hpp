#ifndef DBR_UNICODE_UTF8_IMMUTABLE_STRING_HPP
#define DBR_UNICODE_UTF8_IMMUTABLE_STRING_HPP

#include <memory>

#include "Core.hpp"

namespace dbr
{
	namespace unicode
	{
		namespace utf8
		{
			class ImmutableString
			{
			public:
				ImmutableString();
				ImmutableString(const char* coded);

				// copies count bytes from coded
				ImmutableString(const char* coded, std::size_t count);

				ImmutableString(const ImmutableString& other);
				ImmutableString(ImmutableString&& other);

				~ImmutableString() = default;

				// copies count (or to end of string if npos) characters from start to a new string
				ImmutableString substr(std::size_t start, std::size_t count = npos) const;

				// number of individual characters
				std::size_t charCount() const;

				// returns number of codepoints
				std::size_t codepointCount() const;

				// returns number of bytes
				std::size_t memSize() const;

				bool empty() const;

				// NOT null-terminated
				const char* data() const;

				Char operator[](std::size_t idx) const;

			private:
				std::shared_ptr<char> bytes;

				std::size_t numChars;		// length in characters
				std::size_t numCodepoints;	// length in code points
				std::size_t size;			// size in memory
			};

			std::ostream& operator<<(std::ostream& os, const ImmutableString& str);
		}
	}
}

#endif
