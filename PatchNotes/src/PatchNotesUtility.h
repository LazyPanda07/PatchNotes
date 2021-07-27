#pragma once

#include <cstdint>
#include <utility>

namespace utility
{
	uint32_t getCodepage();

	std::pair<int, int> getScreenCenter(uint16_t width, uint16_t height);
}
