#include "Validation.h"

#include "headers.h"

#include "PatchNotesUtility.h"

#include "Exceptions/ValidationException.h"

using namespace std;

namespace validation
{
	void emptyValidation(const string& data, const wstring& fieldName)
	{
		if (data.empty())
		{
			throw exceptions::ValidationException(format("���� \"{}\" �� ����� ���� ������", gui_framework::utility::to_string(fieldName, utility::getCodepage())));
		}
	}

	void emptyValidation(const wstring& data, const wstring& fieldName)
	{
		if (data.empty())
		{
			throw exceptions::ValidationException(format("���� \"{}\" �� ����� ���� ������", gui_framework::utility::to_string(fieldName, utility::getCodepage())));
		}
	}
}
