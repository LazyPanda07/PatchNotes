#include "PatchNotesUtility.h"

#include "GUIFramework.h"

using namespace std;

namespace utility
{
	uint32_t getCodepage()
	{
		return static_cast<uint32_t>(gui_framework::GUIFramework::get().getJSONSettings().get<int64_t>("codepage"));
	}

	pair<int, int> getScreenCenter(uint16_t width, uint16_t height)
	{
		uint16_t screenWidth = static_cast<uint16_t>(GetSystemMetrics(SM_CXSCREEN));
		uint16_t screenHeight = static_cast<uint16_t>(GetSystemMetrics(SM_CYSCREEN));

		return { (screenWidth - width) / 2, (screenHeight - height) / 2 };
	}

	wstring to_wstring(const string& stringToConvert, uint32_t codepage)
	{
		wstring result;

		int size = MultiByteToWideChar
		(
			codepage,
			NULL,
			stringToConvert.data(),
			-1,
			nullptr,
			NULL
		);

		if (!size)
		{
			throw json::exceptions::WrongEncodingException();
		}

		result.resize(static_cast<size_t>(size) - 1);

		if (!MultiByteToWideChar
		(
			codepage,
			NULL,
			stringToConvert.data(),
			-1,
			result.data(),
			size
		))
		{
			throw json::exceptions::WrongEncodingException();
		}

		return result;
	}
}
