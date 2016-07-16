#include "ImmutableString.hpp"

namespace dbr
{
	namespace unicode
	{
		namespace utf32
		{
			ImmutableString::ImmutableString()
				: bytes(nullptr),
				size(0)
			{}

			ImmutableString::ImmutableString(const char* coded)
				: ImmutableString(coded, bufferLength(coded))
			{}

			ImmutableString::ImmutableString(const Char* coded)
				: ImmutableString(reinterpret_cast<const char*>(coded))
			{}

			ImmutableString::ImmutableString(const char* coded, std::size_t num)
			{
				size = num / sizeof(Char);
				bytes = std::shared_ptr<Char>(new Char[size], std::default_delete<Char[]>{});

				std::copy(coded, coded + num, reinterpret_cast<char*>(bytes.get()));
			}

			ImmutableString::ImmutableString(const Char* coded, std::size_t num)
				: ImmutableString(reinterpret_cast<const char*>(coded), num * sizeof(Char))
			{}

			ImmutableString::ImmutableString(const ImmutableString& other)
				: bytes(other.bytes),
				size(other.size)
			{}

			ImmutableString::ImmutableString(ImmutableString&& other)
				: bytes(std::move(other.bytes)),
				size(other.size)
			{}

			ImmutableString ImmutableString::substr(std::size_t start, std::size_t count) const
			{
				return{reinterpret_cast<const char*>(bytes.get()) + start * sizeof(Char), count * sizeof(Char)};
			}

			std::size_t ImmutableString::charCount() const
			{
				return size;
			}

			std::size_t ImmutableString::codepointCount() const
			{
				return size;
			}

			std::size_t ImmutableString::memSize() const
			{
				return size * sizeof(Char);
			}

			bool ImmutableString::empty() const
			{
				return size == 0;
			}

			const char* ImmutableString::data() const
			{
				return reinterpret_cast<const char*>(bytes.get());
			}

			Char ImmutableString::operator[](std::size_t idx) const
			{
				return bytes.get()[idx];
			}
		}
	}
}
