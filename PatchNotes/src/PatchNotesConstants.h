#pragma once

#include <string>

namespace globals
{
	inline std::string dataFolder;
}

namespace patch_notes_constants
{
	inline const std::wstring successTitle = L"Успех";
	inline const std::wstring errorTitle = L"Ошибка";

	inline const std::string assetsFolder = "assets";

	inline constexpr std::string_view jsonVersionsFolder = "json_versions";

	inline constexpr std::string_view htmlGeneratedFolder = "docs";
}
