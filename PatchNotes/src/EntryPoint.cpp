#include <iostream>

#include "headers.h"
#include "BaseComposites/StandardComposites/BaseDialogBox.h"

#include "Initializer.h"
#include "PatchNotesUtility.h"
#include "PatchNotesConstants.h"

#pragma warning(disable: 28251)

using namespace std;

int wWinMain(HINSTANCE hInstance, HINSTANCE, PWSTR pCmdLine, int nCmdShow)
{
	utility::initPathToPatchNotes(hInstance);

	if (pCmdLine == command_line::restart)
	{
		utility::restart();

		return 0;
	}

	try
	{
		unique_ptr<gui_framework::WindowHolder> holder;

		Initializer::get().initialize(holder);

		holder->runMainLoop();
	}
	catch (const exception& e)
	{
		try
		{
			gui_framework::BaseDialogBox::createMessageBox(utility::to_wstring(e.what(), CP_UTF8), patch_notes_constants::errorTitle, gui_framework::BaseDialogBox::messageBoxType::ok);
		}
		catch (const json::exceptions::CantFindValueException&)
		{
			gui_framework::BaseDialogBox::createMessageBox(L"Can't find gui_framework.json", patch_notes_constants::errorTitle, gui_framework::BaseDialogBox::messageBoxType::ok);
		}
	}

	Initializer::get().removePreviewFiles();

	return 0;
}
