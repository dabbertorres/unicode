#include "Unicode.hpp"

namespace dbr
{
	namespace unicode
	{
		std::size_t bufferLength(const char* buf)
		{
			std::size_t len = 0;

			for(auto* ptr = buf; *ptr != '\0'; ++ptr, ++len);

			return len;
		}
	}
}
