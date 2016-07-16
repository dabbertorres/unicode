#ifndef DBR_UNICODE_CONVERSION_HPP
#define DBR_UNICODE_CONVERSION_HPP

#include "utf8/ImmutableString.hpp"
#include "utf32/ImmutableString.hpp"

namespace dbr
{
	namespace unicode
	{
		utf32::ImmutableString toUTF32(const utf8::ImmutableString& str);
		utf8::ImmutableString toUTF8(const utf32::ImmutableString& str);
	}
}

#endif
