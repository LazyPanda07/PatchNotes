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
}
