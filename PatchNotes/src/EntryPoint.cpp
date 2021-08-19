#include "pch.h"
#include "BaseComposites/StandardComposites/BaseDialogBox.h"

#include "Initializer.h"
#include "PatchNotesUtility.h"
#include "PatchNotesConstants.h"

#pragma warning(disable: 28251)

using namespace std;

int wWinMain(HINSTANCE hInstance, HINSTANCE, PWSTR pCmdLine, int nCmdShow)
{
	try
	{
		unique_ptr<gui_framework::WindowHolder> holder;

		Initializer::get().initialize(holder);

		holder->runMainLoop();
	}
	catch (const exception& e)
	{
		gui_framework::BaseDialogBox::createMessageBox(utility::to_wstring(e.what(), utility::getCodepage()), patch_notes_constants::errorTitle, gui_framework::BaseDialogBox::messageBoxType::ok);
	}

	return 0;
}
