#include <iostream>

#include "GUIFramework.h"
#include "Composites/SeparateWindow.h"
#include "Utility/Holders/WindowHolder.h"

#pragma warning(disable: 28251)

using namespace std;

CREATE_DEFAULT_WINDOW_FUNCTION(patchNotes)

int wWinMain(HINSTANCE hInstance, HINSTANCE, PWSTR pCmdLine, int nCmdShow)
{
	try
	{
		gui_framework::GUIFramework& instance = gui_framework::GUIFramework::get();

		gui_framework::WindowHolder holder(make_unique<gui_framework::SeparateWindow>(L"PatchNotesWindow", L"Patch notes", gui_framework::utility::ComponentSettings(300, 200, 800, 600), "patchNotes"));
		gui_framework::SeparateWindow* mainWindow = dynamic_cast<gui_framework::SeparateWindow*>(holder.get());

		mainWindow->setExitMode(gui_framework::BaseComponent::exitMode::quit);

		holder.runMainLoop();
	}
	catch (const exception& e)
	{
		cout << e.what() << endl;
	}

	return 0;
}
