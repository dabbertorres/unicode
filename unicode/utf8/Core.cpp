#include "Core.hpp"

#include <cmath>
#include <cstring>

namespace dbr
{
	namespace unicode
	{
		namespace utf8
		{
			bool valid(const byte* coded, std::size_t num)
			{
				for(auto ptr = coded; *ptr != '\0' && static_cast<std::size_t>(ptr - coded) < num; ++ptr)
				{
					std::size_t numSeq = 0;
					std::size_t bitPos = 0b10000000;

					auto val = *ptr;

					while(val & bitPos && bitPos != 1)
					{
						bitPos >>= 1;
						++numSeq;
					}

					// UTF-8 does not have more than 4 byte sequences, and we should not encounter 0b10xxxxxx yet
					if(numSeq > 4 || numSeq == 1)
						return false;

					// early exit for 1 byte sequences (marker: 0)
					if(numSeq == 0)
						continue;

					std::size_t bitsFirstByte = 7 - numSeq;				// 7 bits max used for sequence marking
					const std::size_t codingBits = 6 * (numSeq - 1);	// 6 bits per continuation byte for the value
					const std::size_t totalCodingBits = bitsFirstByte + codingBits;

					// for building the U+xxxx hex notation value for checking minimum values
					std::size_t pointVal = (*ptr & static_cast<std::size_t>(std::pow(2u, bitsFirstByte))) << totalCodingBits;

					// move to the next byte in the sequence
					++ptr;

					for(std::size_t i = 1; i < numSeq; ++i, ++ptr)
					{
						// subsequent bytes in a sequence are in the form: 0b10xxxxxx
						if((*ptr & 0b11000000) != 0b10000000)
							return false;

						pointVal += (*ptr & 0b111111) << (codingBits - 6 * i);	// 6 bits per continuation byte for the value
					}

					// check if pointVal is >= the minimum value for that byte sequence

					// reset ptr for outer for loop increment
					--ptr;
				}

				return true;
			}

			bool isDiacritic(const byte* coded)
			{
				std::size_t numSeq = 0;
				std::size_t bitPos = 0b10000000;

				auto val = *coded;

				while(val & bitPos && bitPos != 1)
				{
					bitPos >>= 1;
					++numSeq;
				}

				std::size_t bitsFirstByte = 7 - numSeq;				// 7 bits max used for sequence marking
				const std::size_t codingBits = 6 * (numSeq - 1);	// 6 bits per continuation byte for the value
				const std::size_t totalCodingBits = bitsFirstByte + codingBits;

				// for building the U+xxxx hex notation value for checking minimum values
				std::size_t pointVal = (val & static_cast<std::size_t>(std::pow(2u, bitsFirstByte))) << totalCodingBits;

				auto ptr = ++coded;
				for(std::size_t i = 1; i < numSeq; ++i, ++ptr)
				{
					// subsequent bytes in a sequence are in the form: 0b10xxxxxx
					if((*ptr & 0b11000000) != 0b10000000)
						return false;

					pointVal += (*ptr & 0b111111) << (codingBits - 6 * i);	// 6 bits per continuation byte for the value
				}

				// ranges of diacritical marks from: https://en.wikipedia.org/wiki/Combining_character

				if(0x300 <= pointVal && pointVal <= 0x36f)
					return true;

				if(0x1ab0 <= pointVal && pointVal <= 0x1aff)
					return true;

				if(0x1dc0 <= pointVal && pointVal <= 0x1dff)
					return true;

				if(0x20d0 <= pointVal && pointVal <= 0x20ff)
					return true;

				if(0xfe20 <= pointVal && pointVal <= 0xfe2f)
					return true;

				return false;
			}

			std::size_t codepointLength(const byte* coded)
			{
				std::size_t len = 0;

				for(auto ptr = coded; *ptr != '\0'; ++ptr)
				{
					// the number of codepoints is the number of non-continuation bytes
					if((*ptr & 0b11000000) != 0b10000000)
						++len;
				}

				return len;
			}

			std::size_t characterLength(const byte* coded)
			{
				std::size_t len = 0;

				for(auto ptr = coded; *ptr != '\0'; ++ptr)
				{
					// the number of codepoints is the number of non-continuation bytes
					if((*ptr & 0b11000000) != 0b10000000)
					{
						if(!isDiacritic(ptr))
							++len;
					}
				}

				return len;
			}
		}
	}
}
