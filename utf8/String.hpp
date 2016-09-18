#ifndef DBR_UNICODE_UTF8_STRING_HPP
#define DBR_UNICODE_UTF8_STRING_HPP

#include "Core.hpp"

namespace dbr
{
	namespace unicode
	{
		namespace utf8
		{
			class String
			{
			public:
				String();
				String(const char* coded);

				// copies count bytes from coded
				String(const char* coded, std::size_t count);

				String(const String& other);
				String(String&& other);

				~String() = default;

				// returns number of codepoints in the encoded sequence
				std::size_t codepointCount() const;

				// returns number of bytes
				std::size_t memSize() const;

				const char* data() const;

			private:

			};
		}
	}
}

#endif
