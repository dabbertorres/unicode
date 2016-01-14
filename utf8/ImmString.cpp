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

			// copies 'num' codepoints from 'coded'
			String::String(const byte* coded, std::size_t num)
			:	String()
			{
				if(valid(coded, num))
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

			String::String(const String& other)
			:	bytes(other.bytes),
				size(other.size),
				len(other.len)
			{}

			String::String(String&& other)
			:	bytes(std::move(other.bytes)),
				size(other.size),
				len(other.len)
			{
				other.bytes.reset();
				other.size = 0;
				other.len = 0;
			}

			std::size_t String::length() const
			{
				return len;
			}

			std::size_t String::memSize() const
			{
				return size;
			}

			const byte* String::data() const
			{
				return bytes.get();
			}
		}
	}
}