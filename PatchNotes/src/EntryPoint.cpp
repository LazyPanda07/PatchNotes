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
	utility::createMainWindow();

	while (utility::isRunning())
	{
		this_thread::sleep_for(1s);
	}

	Initializer::get().removePreviewFiles();

	return 0;
}
