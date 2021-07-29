#include "ValidationException.h"

#include "pch.h"

#include "PatchNotesUtility.h"

using namespace std;

namespace exceptions
{
	ValidationException::ValidationException(const string& message) :
		runtime_error(json::utility::toUTF8JSON(message, utility::getCodepage()))
	{

	}

	ValidationException::ValidationException(const wstring& message) :
		runtime_error(json::utility::toUTF8JSON(gui_framework::utility::to_string(message, utility::getCodepage()), utility::getCodepage()))
	{

	}

	wstring ValidationException::getMessage() const
	{
		return utility::to_wstring(this->what(), CP_UTF8);
	}
}
