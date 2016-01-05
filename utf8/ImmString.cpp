#include "ImmString.hpp"

#include <cstring>

#include "InvalidEncoding.hpp"

namespace dbr
{
	namespace utf8
	{
		namespace imm
		{
			String::String()
			:	bytes(nullptr),
				size(0),
				len(0)
			{}

			String::String(const byte* coded)
			:	String()
			{
				if(valid(coded))
				{
					size = std::strlen(coded);
					len = strlen(coded);
					bytes = std::shared_ptr<byte>(new byte[size], std::default_delete<byte[]>());

					auto start = bytes.get();
					std::copy(coded, coded + size, start);
				}
				else
				{
					throw InvalidEncoding("Could not construct imm::String from invalid encoding.");
				}
			}

			std::size_t String::length() const
			{
				return len;
			}

			const byte* String::data() const
			{
				return bytes.get();
			}
		}
	}
}