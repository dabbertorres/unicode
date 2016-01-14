#ifndef DBR_UTF8_INVALID_ENCODING_HPP
#define DBR_UTF8_INVALID_ENCODING_HPP

#include <stdexcept>

namespace dbr
{
	namespace utf8
	{
		class InvalidEncoding : public std::runtime_error
		{
			public:
				InvalidEncoding(const char* msg);
				InvalidEncoding(const std::string& msg);
		};
	}
}

#endif
