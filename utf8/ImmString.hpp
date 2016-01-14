#ifndef DBR_UTF8_IMM_STRING_HPP
#define DBR_UTF8_IMM_STRING_HPP

#include <memory>

#include "Core.hpp"

namespace dbr
{
	namespace utf8
	{
		namespace imm
		{
			class String
			{
				public:
					String();
					String(const byte* coded);

					// copies 'num' codepoints from 'coded'
					String(const byte* coded, std::size_t num);

					String(const String& other);
					String(String&& other);

					~String() = default;

					String substr(std::size_t start = 0, std::size_t count = npos) const;

					// returns number of codepoints in the encoded sequence
					std::size_t length() const;

					// returns number of bytes
					std::size_t memSize() const;

					bool empty() const;

					const byte* data() const;
					
				private:
					std::shared_ptr<byte> bytes;

					std::size_t size;		// size in memory
					std::size_t len;		// length in code points
			};
		}
	}
}

#endif
