#include "Conversion.hpp"

#include <memory>

namespace dbr
{
	namespace unicode
	{
		utf32::ImmutableString toUTF32(const utf8::ImmutableString& str)
		{
			auto* data = str.data();
			
			auto len = utf8::characterLength(data);

			auto out = std::make_unique<utf32::Char[]>(len);

			for(auto i = 0u; i < len; ++i)
			{
				std::size_t seqLen = 0;
				out[i] = utf8::decode(data, seqLen);
				data += seqLen;
			}

			return{out.get()};
		}

		utf8::ImmutableString toUTF8(const utf32::ImmutableString& /*str*/)
		{
			// TODO
			return{};
		}
	}
}
