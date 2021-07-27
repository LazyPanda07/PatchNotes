#include "Initializer.h"

#include "GUIFramework.h"
#include "Composites/DialogBox.h"
#include "MenuItems/MenuItem.h"

#include "PatchNotesConstants.h"

using namespace std;

CREATE_DEFAULT_WINDOW_FUNCTION(patchNotes)

void Initializer::createMenus()
{
	auto& menu = mainWindow->createMainMenu(L"PatchNotesMenu");
	auto createProjectConfiguration = [this]()
	{
		if (projectConfigurationViewRawPointer)
		{
			projectConfigurationController->getModel()->removeObserver(projectConfigurationViewRawPointer);

			projectConfigurationViewRawPointer = nullptr;
		}

		projectConfigurationController = make_shared<controllers::ProjectConfigurationController>();
		unique_ptr<views::interfaces::IObserver> projectConfigurationView = make_unique<views::ProjectConfigurationView>(projectConfigurationController);

		projectConfigurationViewRawPointer = projectConfigurationView.get();

		projectConfigurationController->getModel()->addObserver(move(projectConfigurationView));
	};

	menu->addMenuItem(unique_ptr<gui_framework::interfaces::IMenuItem>(new gui_framework::MenuItem(L"Создать новую конфигурацию", createProjectConfiguration)));
}

Initializer::Initializer() :
	mainWindow(nullptr),
	projectConfigurationViewRawPointer(nullptr)
{

}

void Initializer::initialization(unique_ptr<gui_framework::WindowHolder>& holder)
{
	gui_framework::GUIFramework& instance = gui_framework::GUIFramework::get();
	holder = make_unique<gui_framework::WindowHolder>(make_unique<gui_framework::SeparateWindow>(L"PatchNotesWindow", L"Patch notes", gui_framework::utility::ComponentSettings(300, 200, 800, 600), "patchNotes"));

	dataFolder = (filesystem::current_path() /= "data").string();

	filesystem::create_directory(dataFolder);

	mainWindow = dynamic_cast<gui_framework::SeparateWindow*>(holder->get());

	mainWindow->setExitMode(gui_framework::BaseComponent::exitMode::quit);

	createMenus();
}

