#include "ImmutableString.hpp"

#include <ostream>

#include "InvalidEncoding.hpp"

namespace dbr
{
	namespace unicode
	{
		namespace utf8
		{
			ImmutableString::ImmutableString()
				: bytes(nullptr),
				numChars(0),
				numCodepoints(0),
				size(0)
			{}

			ImmutableString::ImmutableString(const char* coded)
				: ImmutableString()
			{
				if(valid(coded))
				{
					numChars = characterLength(coded);
					numCodepoints = codepointLength(coded);
					size = bufferLength(coded);
					bytes = std::shared_ptr<char>(new char[size], std::default_delete<char[]>{});

					auto start = bytes.get();
					std::copy(coded, coded + size, start);
				}
				else
				{
					throw InvalidEncoding("Could not construct utf8::ImmutableString from invalid encoding.");
				}
			}

			// copies count bytes from coded
			ImmutableString::ImmutableString(const char* coded, std::size_t count)
				: ImmutableString()
			{
				if(valid(coded, count))
				{
					numChars = characterLength(coded, count);
					numCodepoints = codepointLength(coded, count);
					size = count;
					bytes = std::shared_ptr<char>(new char[size], std::default_delete<char[]>{});

					std::copy(coded, coded + size, bytes.get());
				}
				else
				{
					throw InvalidEncoding("Could not construct utf8::ImmutableString from invalid encoding.");
				}
			}

			ImmutableString::ImmutableString(const ImmutableString& other)
				: bytes(other.bytes),
				numChars(other.numChars),
				numCodepoints(other.numCodepoints),
				size(other.size)
			{}

			ImmutableString::ImmutableString(ImmutableString&& other)
				: bytes(std::move(other.bytes)),
				numChars(other.numChars),
				numCodepoints(other.numCodepoints),
				size(other.size)
			{
				other.bytes.reset();
				other.size = 0;
				other.numCodepoints = 0;
			}

			ImmutableString ImmutableString::substr(std::size_t start, std::size_t count) const
			{
				auto startPtr = bytes.get();
				std::size_t memStart = findNthCharacter(bytes.get(), start);

				if(memStart == npos)
					throw std::out_of_range("start");

				startPtr += memStart;

				if(count != npos)
				{
					std::size_t byteCount = findNthCharacter(startPtr, count);

					if(byteCount == npos)
						throw std::out_of_range("start + count");

					return{startPtr, byteCount};
				}
				else
				{
					// to end of string
					return{startPtr};
				}
			}

			std::size_t ImmutableString::charCount() const
			{
				return numChars;
			}

			std::size_t ImmutableString::codepointCount() const
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

			const char* ImmutableString::data() const
			{
				return bytes.get();
			}

			std::ostream& operator<<(std::ostream& os, const ImmutableString& str)
			{
				return os.write(str.data(), str.memSize());
			}
		}
	}
}
