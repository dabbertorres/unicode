#include "InvalidEncoding.hpp"

namespace dbr
{
	namespace utf8
	{
		InvalidEncoding::InvalidEncoding(const char* msg)
		:	std::runtime_error(msg)
		{}

		InvalidEncoding::InvalidEncoding(const std::string& msg)
		:	std::runtime_error(msg)
		{}
	}
}