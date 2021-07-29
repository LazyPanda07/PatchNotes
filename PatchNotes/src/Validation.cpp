#include "Validation.h"

#include "pch.h"

#include "PatchNotesUtility.h"

#include "Exceptions/ValidationException.h"

using namespace std;

namespace validation
{
	void emptyValidation(const string& data, const wstring& fieldName)
	{
		if (data.empty())
		{
			throw exceptions::ValidationException(format(R"(���� "{}" �� ����� ���� ������)", gui_framework::utility::to_string(fieldName, utility::getCodepage())));
		}
	}

	void emptyValidation(const wstring& data, const wstring& fieldName)
	{
		if (data.empty())
		{
			throw exceptions::ValidationException(format(R"(���� "{}" �� ����� ���� ������)", gui_framework::utility::to_string(fieldName, utility::getCodepage())));
		}
	}
}
