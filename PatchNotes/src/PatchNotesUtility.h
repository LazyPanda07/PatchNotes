#pragma once

#include <cstdint>
#include <utility>
#include <string>
#include <filesystem>

#include "JSONParser.h"
#include "JSONBuilder.h"

namespace utility
{
	std::pair<int, int> getScreenCenter(uint16_t width, uint16_t height);

	std::wstring to_wstring(const std::string& stringToConvert, uint32_t codepage);

	void copyJSON(const std::filesystem::path& pathToProjectFile, json::JSONBuilder& outBuilder);

	std::vector<std::wstring> getAvailableProjectsFiles();

	std::vector<std::wstring> getAvailableCategories(const std::wstring& projectName);

	std::vector<std::wstring> getAvailableElements(const std::wstring& projectName, const std::wstring& categoryName);

	std::vector<std::wstring> getAvailableNotes(const std::wstring& projectName, const std::wstring& categoryName, const std::wstring& elementName);
}
