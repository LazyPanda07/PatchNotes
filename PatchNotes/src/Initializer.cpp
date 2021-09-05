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
#include "Views/DeleteCategoryView.h"
#include "Views/DeleteElementView.h"
#include "Views/DeleteNoteView.h"

#include "Controllers/ProjectConfigurationController.h"
#include "Controllers/PatchNotesController.h"
#include "Controllers/CategoryController.h"
#include "Controllers/GenerateHTMLController.h"
#include "Controllers/PreviewPatchNotesController.h"

#include "../resource.h"

#include "Exceptions/ValidationException.h"
#include "PatchNotesConstants.h"
#include "PatchNotesUtility.h"

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

		gui_framework::DropDownListComboBox* currentProject = static_cast<gui_framework::DropDownListComboBox*>(static_cast<gui_framework::BaseComposite*>(mainWindow->findChild(L"PatchNotesUI"))->findChild(L"ProjectNameAndVersion"));
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
			static_cast<::views::GenerateHTMLView*>(generateHTMLView.get())->onClick(patchNotesView->getWindow());
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
			static_cast<::views::PreviewPatchNotesView*>(previewPatchNotesView.get())->onClick(patchNotesView->getWindow());
		}
		catch (const exceptions::ValidationException& e)
		{
			gui_framework::BaseDialogBox::createMessageBox(e.getMessage(), patch_notes_constants::errorTitle, gui_framework::BaseDialogBox::messageBoxType::ok, mainWindow);
		}
	};

	gui_framework::Menu& creationsDropDown = mainWindow->addPopupMenu(L"Creations");
	gui_framework::Menu& deletionsDropDown = mainWindow->addPopupMenu(L"Deletions");

	creationsDropDown.addMenuItem(make_unique<gui_framework::MenuItem>(L"Создать новую конфигурацию", createProjectConfiguration));

	creationsDropDown.addMenuItem(make_unique<gui_framework::MenuItem>(L"Создать новую категорию", createCategory));

	menu->addMenuItem(make_unique<gui_framework::DropDownMenuItem>(L"Создать", creationsDropDown.getHandle()));

	menu->addMenuItem(make_unique<gui_framework::MenuItem>(L"Предпросмотр", previewPatchNotes));

	menu->addMenuItem(make_unique<gui_framework::MenuItem>(L"Сгенерировать список изменений", generateHTML));

	deletionsDropDown.addMenuItem(make_unique<gui_framework::MenuItem>(L"Удалить конфигурацию", [this]() { deleteProjectConfigurationView = make_unique<::views::DeleteProjectConfigurationView>(); }));

	deletionsDropDown.addMenuItem(make_unique<gui_framework::MenuItem>(L"Удалить категорию", [this]() { deleteCategoryView = make_unique<::views::DeleteCategoryView>(); }));

	deletionsDropDown.addMenuItem(make_unique<gui_framework::MenuItem>(L"Удалить элемент", [this]() { deleteElementView = make_unique<::views::DeleteElementView>(); }));

	deletionsDropDown.addMenuItem(make_unique<gui_framework::MenuItem>(L"Удалить описание", [this]() { deleteNoteView = make_unique<::views::DeleteNoteView>(); }));

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
				BaseComposite* parent = static_cast<BaseComposite*>(component->getParent());

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
					BaseComposite* composite = static_cast<BaseComposite*>(component);

					SetFocus(composite->getChildren().front()->getHandle());
				}
			}
		});
}

void Initializer::initBackgroundPatchNotesColor()
{
	string& styles = patch_notes_constants::styles;

	const auto& color = gui_framework::GUIFramework::get().getJSONSettings().getArray("patchNotesBackgroundColor");
	string colorFormat;

	for (const auto& i : color)
	{
		try
		{
			colorFormat += to_string(std::get<int64_t>(i->data.front().second)) + ", ";
		}
		catch (const bad_variant_access&)
		{
			colorFormat += to_string(std::get<double>(i->data.front().second)) + ", ";
		}
	}

	colorFormat.pop_back();
	colorFormat.pop_back();

	styles.replace(styles.find("[1]"), 3, colorFormat);
}

void Initializer::initBackgroundImage()
{
	string& styles = patch_notes_constants::styles;

	try
	{
		styles.replace(styles.find("[0]"), 3, gui_framework::GUIFramework::get().getJSONSettings().getString("pathToBackgroundImage"));
	}
	catch (const bad_variant_access&)
	{
		gui_framework::GUIFramework::get().getJSONSettings().getNull("pathToBackgroundImage");

		HRSRC backgroundResourceHandle = FindResourceA(nullptr, MAKEINTRESOURCEA(DEFAULT_BACKGROUND_IMAGE), "Base64");

		if (backgroundResourceHandle)
		{
			HGLOBAL backgroundDataHandle = LoadResource(nullptr, backgroundResourceHandle);

			if (backgroundDataHandle)
			{
				void* data = LockResource(backgroundDataHandle);

				if (data)
				{
					string tem = format(R"("data:image/png;base64,{}")", string_view(static_cast<char*>(data), SizeofResource(GetModuleHandleW(nullptr), backgroundResourceHandle)));

					styles.replace(styles.find("[0]"), 3, tem);
				}
			}
		}
	}
}

Initializer::Initializer() :
	mainWindow(nullptr),
	isBackgroundImageLoaded(false)
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

void Initializer::closeDeleteConfiguration()
{
	deleteProjectConfigurationView->remove();

	deleteProjectConfigurationView.reset();
}

void Initializer::closeDeleteCategory()
{
	deleteCategoryView->remove();

	deleteCategoryView.reset();
}

void Initializer::closeDeleteElement()
{
	deleteElementView->remove();

	deleteElementView.reset();
}

void Initializer::closeDeleteNote()
{
	deleteNoteView->remove();

	deleteNoteView.reset();
}

void Initializer::initialize(unique_ptr<gui_framework::WindowHolder>& holder)
{
	auto [x, y] = utility::getScreenCenter(sizes::mainWindowWidth, sizes::mainWindowHeight);
	gui_framework::utility::ComponentSettings settings(x, y, sizes::mainWindowWidth, sizes::mainWindowHeight);
	
	holder = make_unique<gui_framework::WindowHolder>(make_unique<gui_framework::SeparateWindow>(L"PatchNotesWindow", L"Patch notes", settings, "patchNotes", false, false, "", APPLICATION_ICON, APPLICATION_ICON));

	globals::dataFolder = (filesystem::path(json::utility::fromUTF8JSON(gui_framework::GUIFramework::get().getJSONSettings().getString("pathToProject"), utility::getCodepage())) /= patch_notes_constants::jsonVersionsFolder).string();

	filesystem::create_directory(globals::dataFolder);

	mainWindow = static_cast<gui_framework::SeparateWindow*>(holder->get());

	mainWindow->setExitMode(gui_framework::BaseComponent::exitMode::quit);

	mainWindow->setAutoResize(true);

	this->createMenus();

	this->createUI();

	this->registerHotkeys();

	this->initBackgroundPatchNotesColor();

	gui_framework::GUIFramework::get().addTask([this]() { this->initBackgroundImage(); }, [this]() { isBackgroundImageLoaded = true; });
}

void Initializer::addPreviewFile(const filesystem::path& previewFile)
{
	if (previewFiles.empty())
	{
		previewFiles.push_back(filesystem::temp_directory_path() / patch_notes_constants::stylesFileName);
	}

	previewFiles.push_back(previewFile);
}

void Initializer::removePreviewFiles()
{
	for (const auto& i : previewFiles)
	{
		filesystem::remove(i);
	}
}

bool Initializer::getIsBackgroundImageLoaded() const
{
	return isBackgroundImageLoaded;
}
