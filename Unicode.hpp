#ifndef DBR_UNICODE_UNICODE_HPP
#define DBR_UNICODE_UNICODE_HPP

#include <cstddef>

namespace dbr
{
	namespace unicode
	{
		static constexpr std::size_t npos = -1;

		// length of a null-terminated buffer
		std::size_t bufferLength(const char* buf);
	}
}

#endif
