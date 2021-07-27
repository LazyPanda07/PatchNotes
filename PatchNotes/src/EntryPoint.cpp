#include <iostream>

#include "GUIFramework.h"
#include "Composites/SeparateWindow.h"
#include "Composites/DialogBox.h"
#include "Utility/Holders/WindowHolder.h"

#include "Views/ProjectConfigurationView.h"
#include "Controllers/ProjectConfigurationController.h"

#include "PatchNotesConstants.h"

#pragma warning(disable: 28251)

using namespace std;

CREATE_DEFAULT_WINDOW_FUNCTION(patchNotes)

int wWinMain(HINSTANCE hInstance, HINSTANCE, PWSTR pCmdLine, int nCmdShow)
{
	try
	{
		gui_framework::GUIFramework& instance = gui_framework::GUIFramework::get();

		dataFolder = (filesystem::current_path() /= "data").string();

		filesystem::create_directory(dataFolder);

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
