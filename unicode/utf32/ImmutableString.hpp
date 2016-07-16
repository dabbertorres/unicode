#ifndef DBR_UNICODE_UTF32_IMMUTABLE_STRING_HPP
#define DBR_UNICODE_UTF32_IMMUTABLE_STRING_HPP

#include <memory>

#include "Core.hpp"

namespace dbr
{
	namespace unicode
	{
		namespace utf32
		{
			class ImmutableString
			{
			public:
				ImmutableString();

				// copies from coded
				ImmutableString(const char* coded);
				ImmutableString(const Char* coded);

				// copies num bytes from coded
				ImmutableString(const char* coded, std::size_t num);

				// copies num Chars from coded
				ImmutableString(const Char* coded, std::size_t num);

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
				std::shared_ptr<Char> bytes;

				std::size_t size;	// in characters
			};
		}
	}
}

#endif
