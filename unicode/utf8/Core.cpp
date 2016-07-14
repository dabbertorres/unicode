#include "Core.hpp"

#include "InvalidEncoding.hpp"

namespace dbr
{
	namespace unicode
	{
		namespace utf8
		{
			std::size_t sequenceLength(const char* coded)
			{
				auto lengthBits = (*coded) >> 4 & 0xf;

				switch(lengthBits)
				{
					// 11110xxx
					case 0xf:
						return 4;

					// 1110xxxx
					case 0xe:
						return 3;

					// 110xxxxx
					case 0xc:
						return 2;

					// 0xxxxxxx
					default:
						return 1;

					// continuation byte
					case 0x8:
						return 0;
				}
			}

			std::uint32_t decode(const char* coded)
			{
				std::size_t dummy;
				return decode(coded, dummy);
			}

			std::uint32_t decode(const char* coded, std::size_t& length)
			{
				length = sequenceLength(coded);

				// UTF-8 does not have more than 4 byte sequences
				if(length > 4)
					throw InvalidEncoding("Sequence has an invalid length");
				else if(length == 0)
					throw InvalidEncoding("Sequence starts with continutation byte");

				// 7 bits max from first byte, and 6 bits per continuation byte
				const auto numBits = (7 - length) + 6 * (length - 1);

				std::uint32_t seq = 0;

				// get bits from first byte
				switch(length)
				{
					case 1:
						seq = (coded[0] & 0x7f);
						break;

					case 2:
						seq = coded[0] & 0x1f;
						break;

					case 3:
						seq = coded[0] & 0x0f;
						break;

					case 4:
						seq = coded[0] & 0x03;
						break;
				}

				seq <<= 6 * (length - 1);

				// add in continuation bytes
				for(auto i = 1u; i < length; ++i)
				{
					seq += (coded[i] & 0x3f) << (numBits - 6 * i);
				}

				return seq;
			}

			std::size_t valid(const char* coded, std::size_t count)
			{
				auto ptr = coded;

				while(*ptr != '\0' && static_cast<std::size_t>(ptr - coded) < count)
				{
					auto len = sequenceLength(ptr);

					if(len != 0)
						ptr += len;
					else
						return ptr - coded;
				}

				return npos;
			}

			bool isDiacritic(const char* coded)
			{
				std::size_t len;
				auto val = decode(coded, len);

				return isDiacritic(val);
			}

			bool isDiacritic(std::uint32_t value)
			{
				// ranges of diacritical marks from: https://en.wikipedia.org/wiki/Combining_character

				if(0x300 <= value && value < 0x370)
					return true;
				else if(0x1ab0 <= value && value < 0x1b00)
					return true;
				else if(0x1dc0 <= value && value < 0x1e00)
					return true;
				else if(0x20d0 <= value && value < 0x2100)
					return true;
				else if(0xfe20 <= value && value < 0xfe30)
					return true;
				else
					return false;
			}

			std::size_t codepointLength(const char* coded, std::size_t count)
			{
				std::size_t len = 0;
				auto ptr = coded;

				while(*ptr != '\0' && static_cast<std::size_t>(ptr - coded) < count)
				{
					ptr += sequenceLength(ptr);
					++len;
				}

				return len;
			}

			std::size_t characterLength(const char* coded, std::size_t count)
			{
				std::size_t len = 0;
				auto ptr = coded;

				while(*ptr != '\0' && static_cast<std::size_t>(ptr - coded) < count)
				{
					std::size_t valLen = 0;
					auto val = decode(ptr, valLen);

					// a codepoint is only a character if it is not a diacritic
					if(!isDiacritic(val))
						++len;

					ptr += valLen;
				}

				return len;
			}

			std::size_t findNthCodepoint(const char* coded, std::size_t nth)
			{
				auto ptr = coded;

				for(auto i = 0u; i < nth; ++i)
				{
					if(*ptr == '\0')
						return npos;

					ptr += sequenceLength(ptr);
				}

				return ptr - coded;
			}

			std::size_t findNthCharacter(const char* coded, std::size_t nth)
			{
				auto ptr = coded;

				for(auto i = 0u; i < nth; ++i)
				{
					if(*ptr == '\0')
						return npos;

					std::size_t len = 0;
					auto val = decode(ptr, len);

					// diacritic marks aren't characters
					if(isDiacritic(val))
						--i;

					ptr += sequenceLength(ptr);
				}

				return ptr - coded;
			}
		}
	}
}
