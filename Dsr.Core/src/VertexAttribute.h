#pragma once

#include <cstddef>

namespace dsr
{
	struct VertexAttribute
	{
		unsigned int Location;
		std::size_t Size;
		bool Normalize;

		VertexAttribute(
			const unsigned int& location,
			const std::size_t& size)
			: VertexAttribute(location, size, false)
		{
		}

		VertexAttribute(
			const unsigned int& location,
			const std::size_t& size,
			const bool& normalize)
			: Location(location), Size(size), Normalize(normalize)
		{
		}
	};
}
