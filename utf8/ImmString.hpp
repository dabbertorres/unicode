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

					~String() = default;

					// returns number of codepoints in the encoded sequence
					std::size_t length() const;

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
