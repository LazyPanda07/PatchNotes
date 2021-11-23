#include "Validation.h"

#include "headers.h"

#include "PatchNotesUtility.h"
#include "PatchNotesConstants.h"

#include "Exceptions/ValidationException.h"

using namespace std;

namespace validation
{
	void emptyValidation(const wstring& data, const wstring& fieldName)
	{
		if (data.empty())
		{
			throw exceptions::ValidationException(format(localization::WTextLocalization::get()[patch_notes_localization::fieldCantBeEmpty], fieldName));
		}
	}
}
