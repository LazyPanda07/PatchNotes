#include "Initializer.h"

#include "GUIFramework.h"
#include "Composites/DialogBox.h"
#include "MenuItems/MenuItem.h"

#include "Views/ProjectConfigurationView.h"
#include "Views/PatchNotesView.h"
#include "Views/CategoryConfigurationView.h"
#include "Views/GenerateHTMLView.h"

#include "Controllers/ProjectConfigurationController.h"
#include "Controllers/PatchNotesController.h"
#include "Controllers/CategoryConfigurationController.h"
#include "Controllers/GenerateHTMLController.h"

#include "PatchNotesConstants.h"
#include "PatchNotesUtility.h"
#include "HTMLAdapter.h"

using namespace std;

CREATE_DEFAULT_WINDOW_FUNCTION(patchNotes)

void Initializer::createMenus()
{
	auto& menu = mainWindow->createMainMenu(L"PatchNotesMenu");
	auto createProjectConfiguration = [this]()
	{
		projectConfigurationView = make_unique<views::ProjectConfigurationView>(patchNotesView->getController());
	};
	auto createCategoryConfiguration = [this]()
	{
		gui_framework::DropDownListComboBox* currentProject = dynamic_cast<gui_framework::DropDownListComboBox*>(dynamic_cast<gui_framework::BaseComposite*>(mainWindow->findChild(L"PatchNotesUI"))->findChild(L"ProjectNameAndVersion"));
		wstring projectNameAndVersion;

		if (int index = currentProject->getCurrentSelectionIndex() != -1)
		{
			projectNameAndVersion = currentProject->getValue(index);
		}

		categoryConfigurationView = make_unique<views::CategoryConfigurationView>(projectNameAndVersion, patchNotesView->getController());
	};
	auto generateHTML = [this]()
	{
		generateHTMLView = make_unique<views::GenerateHTMLView>(mainWindow);

		dynamic_cast<views::GenerateHTMLView*>(generateHTMLView.get())->onClick(patchNotesView->getWindow());
	};

	menu->addMenuItem(unique_ptr<gui_framework::interfaces::IMenuItem>(new gui_framework::MenuItem(L"Создать новую конфигурацию", createProjectConfiguration)));
	
	menu->addMenuItem(unique_ptr<gui_framework::interfaces::IMenuItem>(new gui_framework::MenuItem(L"Создать новую категорию", createCategoryConfiguration)));
	
	menu->addMenuItem(unique_ptr<gui_framework::interfaces::IMenuItem>(new gui_framework::MenuItem(L"Сгенерировать HTML", generateHTML)));
}

void Initializer::createUI()
{
	patchNotesView = make_unique<views::PatchNotesView>(mainWindow);
}

Initializer::Initializer() :
	mainWindow(nullptr)
{

}

void Initializer::initialization(unique_ptr<gui_framework::WindowHolder>& holder)
{
	gui_framework::GUIFramework::get();

	auto [x, y] = utility::getScreenCenter(1024, 768);
	gui_framework::utility::ComponentSettings settings(x, y, 1024, 768);
	
	holder = make_unique<gui_framework::WindowHolder>(make_unique<gui_framework::SeparateWindow>(L"PatchNotesWindow", L"Patch notes", settings, "patchNotes"));

	dataFolder = (filesystem::current_path() /= "data").string();

	filesystem::create_directory(dataFolder);

	mainWindow = dynamic_cast<gui_framework::SeparateWindow*>(holder->get());

	mainWindow->setExitMode(gui_framework::BaseComponent::exitMode::quit);

	gui_framework::utility::removeStyle(mainWindow->getHandle(), WS_THICKFRAME);

	gui_framework::utility::removeStyle(mainWindow->getHandle(), WS_MAXIMIZEBOX);

	this->createUI();
	
	this->createMenus();
}
