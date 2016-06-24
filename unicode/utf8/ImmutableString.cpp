#include "ImmutableString.hpp"

#include <cstring>

#include "InvalidEncoding.hpp"

namespace dbr
{
	namespace unicode
	{
		namespace utf8
		{
			ImmutableString::ImmutableString()
			:	bytes(nullptr),
				numChars(0),
				numCodepoints(0),
				size(0)
			{}

			ImmutableString::ImmutableString(const byte* coded)
			:	ImmutableString()
			{
				if(valid(coded))
				{
					numChars = characterLength(coded);
					numCodepoints = codepointLength(coded);
					size = std::strlen(coded);
					bytes = std::shared_ptr<byte>(new byte[size], std::default_delete<byte[]>{});

					auto start = bytes.get();
					std::copy(coded, coded + size, start);
				}
				else
				{
					throw InvalidEncoding("Could not construct imm::ImmutableString from invalid encoding.");
				}
			}

			// copies 'num' codepoints from 'coded'
			ImmutableString::ImmutableString(const byte* coded, std::size_t num)
			:	ImmutableString()
			{
				if(valid(coded, num))
				{
					numChars = characterLength(coded);
					numCodepoints = codepointLength(coded);
					size = std::strlen(coded);
					bytes = std::shared_ptr<byte>(new byte[size], std::default_delete<byte[]>{});

					auto start = bytes.get();
					std::copy(coded, coded + size, start);
				}
				else
				{
					throw InvalidEncoding("Could not construct imm::ImmutableString from invalid encoding.");
				}
			}

			ImmutableString::ImmutableString(const ImmutableString& other)
			:	bytes(other.bytes),
				numChars(other.numChars),
				numCodepoints(other.numCodepoints),
				size(other.size)
			{}

			ImmutableString::ImmutableString(ImmutableString&& other)
			:	bytes(std::move(other.bytes)),
				numChars(other.numChars),
				numCodepoints(other.numCodepoints),
				size(other.size)
			{
				other.bytes.reset();
				other.size = 0;
				other.numCodepoints = 0;
			}

			std::size_t ImmutableString::chars() const
			{
				return numChars;
			}

			std::size_t ImmutableString::codepoints() const
			{
				return numCodepoints;
			}

			std::size_t ImmutableString::memSize() const
			{
				return size;
			}

			bool ImmutableString::empty() const
			{
				return numCodepoints == 0;
			}

			const byte* ImmutableString::data() const
			{
				return bytes.get();
			}
		}
	}
}
