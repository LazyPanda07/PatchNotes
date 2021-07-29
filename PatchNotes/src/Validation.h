#pragma once

#include <string>

namespace validation
{
	void emptyValidation(const std::string& data, const std::wstring& fieldName);

	void emptyValidation(const std::wstring& data, const std::wstring& fieldName);
}
