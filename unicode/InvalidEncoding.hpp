#ifndef DBR_UNICODE_INVALID_ENCODING_HPP
#define DBR_UNICODE_INVALID_ENCODING_HPP

#include <stdexcept>

namespace dbr
{
	namespace unicode
	{
		class InvalidEncoding : public std::range_error
		{
			public:
				using std::range_error::range_error;
		};
	}
}

#endif
