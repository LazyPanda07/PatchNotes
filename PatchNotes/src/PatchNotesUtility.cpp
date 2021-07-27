#include "PatchNotesUtility.h"

#include "GUIFramework.h"

using namespace std;

namespace utility
{
	uint32_t getCodepage()
	{
		return static_cast<uint32_t>(gui_framework::GUIFramework::get().getJSONSettings().get<uint64_t>("codepage"));
	}
}
