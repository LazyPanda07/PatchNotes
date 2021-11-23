#include "ValidationException.h"

#include "headers.h"

#include "PatchNotesUtility.h"

using namespace std;

namespace exceptions
{
	ValidationException::ValidationException(const wstring& message) :
		runtime_error(gui_framework::utility::to_string(message, CP_UTF8))
	{

	}

	wstring ValidationException::getMessage() const
	{
		return utility::to_wstring(this->what(), CP_UTF8);
	}
}
