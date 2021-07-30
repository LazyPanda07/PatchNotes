#include "Initializer.h"

#include "GUIFramework.h"
#include "Composites/DialogBox.h"
#include "MenuItems/MenuItem.h"

#include "PatchNotesConstants.h"
#include "PatchNotesUtility.h"

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
		unique_ptr<views::interfaces::IObserver> projectConfigurationView = make_unique<views::ProjectConfigurationView>(projectConfigurationController, patchNotesController);

		projectConfigurationViewRawPointer = projectConfigurationView.get();

		projectConfigurationController->getModel()->addObserver(move(projectConfigurationView));
	};
	auto createCategoryConfiguration = [this]()
	{
		if (categoryConfigurationViewRawPointer)
		{
			categoryConfigurationController->getModel()->removeObserver(categoryConfigurationViewRawPointer);

			categoryConfigurationViewRawPointer = nullptr;
		}

		gui_framework::BaseComposite* ui = dynamic_cast<gui_framework::BaseComposite*>(mainWindow->findChild(L"PatchNotesUI"));
		gui_framework::DropDownListComboBox* currentProject = dynamic_cast<gui_framework::DropDownListComboBox*>(ui->findChild(L"ProjectNameAndVersion"));
		const wstring& projectNameAndVersion = currentProject->getCurrentSelectionIndex() == -1 ? L"" : currentProject->getValue(currentProject->getCurrentSelectionIndex());

		categoryConfigurationController = make_shared<controllers::CategoryConfigurationController>();
		unique_ptr<views::interfaces::IObserver> categoryConfigurationView = make_unique<views::CategoryConfigurationView>(categoryConfigurationController, projectNameAndVersion, patchNotesController);

		categoryConfigurationViewRawPointer = categoryConfigurationView.get();

		categoryConfigurationController->getModel()->addObserver(move(categoryConfigurationView));
	};

	menu->addMenuItem(unique_ptr<gui_framework::interfaces::IMenuItem>(new gui_framework::MenuItem(L"Создать новую конфигурацию", createProjectConfiguration)));

	menu->addMenuItem(unique_ptr<gui_framework::interfaces::IMenuItem>(new gui_framework::MenuItem(L"Создать новую категорию", createCategoryConfiguration)));
}

void Initializer::createUI()
{
	patchNotesController = make_shared<controllers::PatchNotesController>();
	unique_ptr<views::interfaces::IObserver> patchNotesView = make_unique<views::PatchNotesView>(patchNotesController, mainWindow);

	patchNotesController->getModel()->addObserver(move(patchNotesView));
}

Initializer::Initializer() :
	mainWindow(nullptr),
	projectConfigurationViewRawPointer(nullptr),
	categoryConfigurationViewRawPointer(nullptr)
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

	this->createMenus();

	this->createUI();
}

