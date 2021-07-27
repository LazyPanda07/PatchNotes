#pragma once

#include <cstdint>
#include <utility>
#include <string>

namespace utility
{
	uint32_t getCodepage();

	std::pair<int, int> getScreenCenter(uint16_t width, uint16_t height);

	std::wstring to_wstring(const std::string& stringToConvert, uint32_t codepage);
}
