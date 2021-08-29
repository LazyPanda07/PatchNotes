#include "Initializer.h"

#include "GUIFramework.h"
#include "Composites/DialogBox.h"
#include "MenuItems/MenuItem.h"
#include "MenuItems/DropDownMenuItem.h"

#include "Views/ProjectConfigurationView.h"
#include "Views/PatchNotesView.h"
#include "Views/CategoryView.h"
#include "Views/GenerateHTMLView.h"
#include "Views/PreviewPatchNotesView.h"
#include "Views/DeleteProjectConfigurationView.h"

#include "Controllers/ProjectConfigurationController.h"
#include "Controllers/PatchNotesController.h"
#include "Controllers/CategoryController.h"
#include "Controllers/GenerateHTMLController.h"
#include "Controllers/PreviewPatchNotesController.h"
#include "Controllers/DeleteProjectConfigurationController.h"

#include "../resource.h"

#include "Exceptions/ValidationException.h"
#include "PatchNotesConstants.h"
#include "PatchNotesUtility.h"
#include "HTMLAdapter.h"

using namespace std;

CREATE_DEFAULT_WINDOW_FUNCTION(patchNotes)

void Initializer::createMenus()
{
	unique_ptr<gui_framework::Menu>& menu = mainWindow->createMainMenu(L"PatchNotesMenu");
	auto createProjectConfiguration = [this]()
	{
		if (projectConfigurationView)
		{
			projectConfigurationView->remove();
		}

		projectConfigurationView = make_unique<::views::ProjectConfigurationView>();
	};
	auto createCategory = [this]()
	{
		if (categoryConfigurationView)
		{
			categoryConfigurationView->remove();
		}

		gui_framework::DropDownListComboBox* currentProject = dynamic_cast<gui_framework::DropDownListComboBox*>(dynamic_cast<gui_framework::BaseComposite*>(mainWindow->findChild(L"PatchNotesUI"))->findChild(L"ProjectNameAndVersion"));
		wstring projectNameAndVersion;

		if (currentProject->getCurrentSelectionIndex() != -1)
		{
			projectNameAndVersion = currentProject->getValue(currentProject->getCurrentSelectionIndex());
		}

		try
		{
			categoryConfigurationView = make_unique<::views::CategoryView>(projectNameAndVersion);
		}
		catch (const exceptions::ValidationException& e)
		{
			gui_framework::BaseDialogBox::createMessageBox(e.getMessage(), patch_notes_constants::errorTitle, gui_framework::BaseDialogBox::messageBoxType::ok, mainWindow);
		}
	};
	auto generateHTML = [this]()
	{
		generateHTMLView = make_unique<::views::GenerateHTMLView>(mainWindow);

		try
		{
			dynamic_cast<::views::GenerateHTMLView*>(generateHTMLView.get())->onClick(patchNotesView->getWindow());
		}
		catch (const exceptions::ValidationException& e)
		{
			gui_framework::BaseDialogBox::createMessageBox(e.getMessage(), patch_notes_constants::errorTitle, gui_framework::BaseDialogBox::messageBoxType::ok, mainWindow);
		}
	};
	auto previewPatchNotes = [this]()
	{
		previewPatchNotesView = make_unique<::views::PreviewPatchNotesView>(mainWindow);

		try
		{
			dynamic_cast<::views::PreviewPatchNotesView*>(previewPatchNotesView.get())->onClick(patchNotesView->getWindow());
		}
		catch (const exceptions::ValidationException& e)
		{
			gui_framework::BaseDialogBox::createMessageBox(e.getMessage(), patch_notes_constants::errorTitle, gui_framework::BaseDialogBox::messageBoxType::ok, mainWindow);
		}
	};
	auto deleteProjectConfiguration = [this]()
	{
		deleteProjectConfigurationView = make_unique<::views::DeleteProjectConfigurationView>();

		try
		{
			dynamic_cast<::views::DeleteProjectConfigurationView*>(deleteProjectConfigurationView.get())->onClick(patchNotesView->getWindow());
		}
		catch (const exceptions::ValidationException& e)
		{
			gui_framework::BaseDialogBox::createMessageBox(e.getMessage(), patch_notes_constants::errorTitle, gui_framework::BaseDialogBox::messageBoxType::ok, mainWindow);
		}
	};
	auto deleteCategory = [this]()
	{

	};
	auto deleteElement = [this]()
	{

	};
	auto deleteNote = [this]()
	{

	};

	gui_framework::Menu& creationsDropDown = mainWindow->addPopupMenu(L"Creations");
	gui_framework::Menu& deletionsDropDown = mainWindow->addPopupMenu(L"Deletions");

	creationsDropDown.addMenuItem(make_unique<gui_framework::MenuItem>(L"Создать новую конфигурацию", createProjectConfiguration));

	creationsDropDown.addMenuItem(make_unique<gui_framework::MenuItem>(L"Создать новую категорию", createCategory));

	menu->addMenuItem(make_unique<gui_framework::DropDownMenuItem>(L"Создать", creationsDropDown.getHandle()));

	menu->addMenuItem(make_unique<gui_framework::MenuItem>(L"Предпросмотр", previewPatchNotes));

	menu->addMenuItem(make_unique<gui_framework::MenuItem>(L"Сгенерировать HTML", generateHTML));

	deletionsDropDown.addMenuItem(make_unique<gui_framework::MenuItem>(L"Удалить конфигурацию", deleteProjectConfiguration));

	deletionsDropDown.addMenuItem(make_unique<gui_framework::MenuItem>(L"Удалить категорию", deleteCategory));

	deletionsDropDown.addMenuItem(make_unique<gui_framework::MenuItem>(L"Удалить элемент", deleteElement));

	deletionsDropDown.addMenuItem(make_unique<gui_framework::MenuItem>(L"Удалить описание", deleteNote));

	menu->addMenuItem(make_unique<gui_framework::DropDownMenuItem>(L"Удалить", deletionsDropDown.getHandle()));
}

void Initializer::registerHotkeys()
{
	gui_framework::GUIFramework& framework = gui_framework::GUIFramework::get();

	framework.registerHotkey(VK_TAB, [&framework]()
		{
			using namespace gui_framework;

			BaseComponent* component = framework.findComponent(GetFocus());

			if (component)
			{
				BaseComposite* parent = dynamic_cast<BaseComposite*>(component->getParent());

				if (parent)
				{
					auto& children = parent->getChildren();

					for (size_t i = 0; i < children.size(); i++)
					{
						if (children[i].get() == component)
						{
							if (i + 1 == children.size())
							{
								SetFocus(children.front()->getHandle());
							}
							else
							{
								SetFocus(children[i + 1]->getHandle());
							}

							return;
						}
					}
				}
				else if (component->isComposite())
				{
					BaseComposite* composite = dynamic_cast<BaseComposite*>(component);

					SetFocus(composite->getChildren().front()->getHandle());
				}
			}
		});
}

Initializer::Initializer() :
	mainWindow(nullptr)
{

}

Initializer& Initializer::get()
{
	static Initializer instance;

	return instance;
}

void Initializer::createUI()
{
	if (patchNotesView)
	{
		patchNotesView->remove();
	}

	patchNotesView = make_unique<::views::PatchNotesView>(mainWindow);
}

void Initializer::closeCategory()
{
	categoryConfigurationView->remove();

	categoryConfigurationView.reset();
}

void Initializer::closeProjectConfiguration()
{
	projectConfigurationView->remove();

	projectConfigurationView.reset();
}

void Initializer::initialize(unique_ptr<gui_framework::WindowHolder>& holder)
{
	gui_framework::GUIFramework::get();

	auto [x, y] = utility::getScreenCenter(1024, 768);
	gui_framework::utility::ComponentSettings settings(x, y, 1024, 768);

	holder = make_unique<gui_framework::WindowHolder>(make_unique<gui_framework::SeparateWindow>(L"PatchNotesWindow", L"Patch notes", settings, "patchNotes", false, false, "", APPLICATION_ICON, APPLICATION_ICON));

	globals::dataFolder = (filesystem::path(json::utility::fromUTF8JSON(gui_framework::GUIFramework::get().getJSONSettings().getString("pathToProject"), utility::getCodepage())) /= patch_notes_constants::jsonVersionsFolder).string();

	filesystem::create_directory(globals::dataFolder);

	mainWindow = dynamic_cast<gui_framework::SeparateWindow*>(holder->get());

	mainWindow->setExitMode(gui_framework::BaseComponent::exitMode::quit);

	gui_framework::utility::removeStyle(mainWindow->getHandle(), WS_THICKFRAME);
	
	gui_framework::utility::removeStyle(mainWindow->getHandle(), WS_MAXIMIZEBOX);

	this->createUI();

	this->createMenus();

	this->registerHotkeys();
}

void Initializer::addPreviewFile(const filesystem::path& previewFile)
{
	previewFiles.push_back(previewFile);
}

void Initializer::removePreviewFiles()
{
	for (const auto& i : previewFiles)
	{
		filesystem::remove(i);
	}
}
