#ifndef DBR_UTF8_STRING_HPP
#define DBR_UTF8_STRING_HPP

#include "Core.hpp"

namespace dbr
{
	namespace utf8
	{
		class String
		{
			public:
				String();
				String(const byte* coded);

				String(const String& other);
				String(String&& other);

				~String() = default;

				// returns number of codepoints in the encoded sequence
				std::size_t length() const;

				// returns number of bytes
				std::size_t memSize() const;

				const byte* data() const;

			private:
				
		};
	}
}

#endif