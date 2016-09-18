#include "Unicode.hpp"

namespace dbr
{
	namespace unicode
	{
		std::size_t bufferLength(const char* buf)
		{
			auto* ptr = buf
			for(; *ptr != '\0'; ++ptr);

			return ptr - buf;
		}
	}
}
