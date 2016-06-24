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
				ImmutableString(const byte* coded);

				// copies 'num' codepoints from 'coded'
				ImmutableString(const byte* coded, std::size_t num);

				ImmutableString(const ImmutableString& other);
				ImmutableString(ImmutableString&& other);

				~ImmutableString() = default;

				ImmutableString substr(std::size_t start = 0, std::size_t count = npos) const;

				// number of individual characters
				std::size_t chars() const;

				// returns number of codepoints
				std::size_t codepoints() const;

				// returns number of bytes
				std::size_t memSize() const;

				bool empty() const;

				const byte* data() const;

			private:
				std::shared_ptr<byte> bytes;

				std::size_t numChars;		// length in characters
				std::size_t numCodepoints;	// length in code points
				std::size_t size;			// size in memory
			};
		}
	}
}

#endif
