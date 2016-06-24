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
				ImmutableString(const byte* coded);

				// copies 'num' codepoints from 'coded'
				ImmutableString(const byte* coded, std::size_t num);

				ImmutableString(const ImmutableString& other);
				ImmutableString(ImmutableString&& other);

				~ImmutableString() = default;

				ImmutableString substr(std::size_t start = 0, std::size_t count = npos) const;

				// returns number of codepoints in the encoded sequence
				std::size_t codepoints() const;

				// returns number of bytes
				std::size_t memSize() const;

				bool empty() const;

				const byte* data() const;

			private:
				std::shared_ptr<byte> bytes;

				std::size_t size;		// size in memory
				std::size_t numCodepoints;		// length in code points
			};
		}
	}
}

#endif
