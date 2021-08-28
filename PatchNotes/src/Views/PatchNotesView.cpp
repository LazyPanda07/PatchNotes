#include "PatchNotesView.h"

#include "Composites/ChildWindow.h"
#include "Components/ComboBoxes/DropDownListComboBox.h"
#include "Components/EditControl.h"
#include "Components/RichEdit.h"
#include "Components/Buttons/Button.h"
#include "Composites/DialogBox.h"
#include "Components/ProgressBars/ProgressBar.h"

#include "Initializer.h"
#include "Controllers/PatchNotesController.h"
#include "PatchNotesConstants.h"
#include "PatchNotesUtility.h"

#include "Exceptions/ValidationException.h"

using namespace std;

CREATE_DEFAULT_WINDOW_FUNCTION(patchNotesUI)

namespace views
{
	gui_framework::BaseComposite* PatchNotesView::createPatchNotesWindow(const unique_ptr<controllers::BaseController>& controller, gui_framework::BaseComponent* parent)
	{
		using namespace gui_framework;

		uint16_t width = parent->getDesiredWidth();
		uint16_t height = parent->getDesiredHeight();

		gui_framework::utility::ComponentSettings settings(0, 0, width - 17, height - 60);
		ChildWindow* patchNotesWindow = new ChildWindow(L"PatchNotesUI", L"PatchNotesUI", settings, parent, "patchNotesUI");

		DropDownListComboBox* currentProject = new DropDownListComboBox(L"ProjectNameAndVersion", gui_framework::utility::ComponentSettings(width / 4, 0, width / 2, 20), patchNotesWindow);
		vector<wstring> projects = PatchNotesView::getAvailableProjectsFiles();

		for (const auto& i : projects)
		{
			currentProject->addValue(i);
		}

		if (projects.size())
		{
			currentProject->setCurrentSelection(0);
		}

		DropDownListComboBox* currentCategory = new DropDownListComboBox(L"ProjectCategory", gui_framework::utility::ComponentSettings(width / 4, 25, width / 2, 20), patchNotesWindow);

		if (currentProject->getCurrentSelectionIndex() != -1)
		{
			vector<wstring> categories = PatchNotesView::getProjectCategories(currentProject->getValue(currentProject->getCurrentSelectionIndex()));

			for (const auto& i : categories)
			{
				currentCategory->addValue(i);
			}

			if (categories.size())
			{
				currentCategory->setCurrentSelection(0);
			}
		}

		EditControl* element = new EditControl(L"Item", width / 4, 50, patchNotesWindow, width / 2 + 10);	// + 10 make element same size as currentProject and currentCategory

		element->setPlaceholder(L"Элемент");

		new RichEdit(L"Notes", gui_framework::utility::ComponentSettings(0, 70, width - 20, height - 170), patchNotesWindow, true);

		new Button(L"AddNotes", L"Добавить", 0, height - 100, patchNotesWindow, [&controller, patchNotesWindow]()
			{
				try
				{
					controller->receiveData(patchNotesWindow);
				}
				catch (const exceptions::ValidationException& e)
				{
					BaseDialogBox::createMessageBox(e.getMessage(), L"Ошибка", BaseDialogBox::messageBoxType::ok, patchNotesWindow);
				}
			}, 200, 40);

		new ProgressBar(L"GenerateHTMLProgressBar", gui_framework::utility::ComponentSettings(200, height - 100, 824, 40), patchNotesWindow);

		currentProject->setOnSelectionChange([currentCategory](gui_framework::BaseComboBox& comboBox)
			{
				if (comboBox.getCurrentSelectionIndex() != -1)
				{
					currentCategory->clear();

					vector<wstring> categories = PatchNotesView::getProjectCategories(comboBox.getValue(comboBox.getCurrentSelectionIndex()));

					for (const auto& i : categories)
					{
						currentCategory->addValue(i);
					}

					if (categories.size())
					{
						currentCategory->setCurrentSelection(0);
					}
				}
			});

		return patchNotesWindow;
	}

	vector<wstring> PatchNotesView::getAvailableProjectsFiles()
	{
		vector<wstring> result;
		map<filesystem::file_time_type, wstring> lastTimeModifiedFiles;

		filesystem::directory_iterator it(globals::dataFolder);

		for (const auto& projectFile : it)
		{
			lastTimeModifiedFiles[filesystem::last_write_time(projectFile)] = projectFile.path().stem().wstring();
		}

		result.reserve(lastTimeModifiedFiles.size());

		for_each(lastTimeModifiedFiles.rbegin(), lastTimeModifiedFiles.rend(), [&result](const pair<filesystem::file_time_type, wstring>& value) { result.push_back(value.second); });

		return result;
	}

	vector<wstring> PatchNotesView::getProjectCategories(const wstring& projectName)
	{
		vector<wstring> result;
		json::JSONParser parser;
		filesystem::path pathToProject;

		pathToProject.append(globals::dataFolder).append(projectName) += (".json");

		ifstream(pathToProject) >> parser;

		for (const auto& i : parser)
		{
			if (i->second.index() == static_cast<size_t>(json::utility::variantTypeEnum::jJSONObject))
			{
				const json::utility::objectSmartPointer<json::utility::jsonObject>& object = get<json::utility::objectSmartPointer<json::utility::jsonObject>>(i->second);
				const string& type = get<string>(
					find_if(object->data.begin(), object->data.end(), [](const pair<string, json::utility::jsonObject::variantType>& value) { return value.first == "type"; })->second
					);

				if (type == "category")
				{
					result.push_back(utility::to_wstring(i->first, CP_UTF8));
				}
			}
		}

		return result;
	}

	PatchNotesView::PatchNotesView(gui_framework::BaseComponent* parent) :
		BaseView(make_unique<controllers::PatchNotesController>(), PatchNotesView::createPatchNotesWindow(controller, parent))
	{

	}

	void PatchNotesView::update(const json::JSONParser& data)
	{
		using gui_framework::BaseDialogBox;

		bool success = data.getBool("success");
		string message = data.getString("message");

		if (success)
		{
			if (BaseDialogBox::createMessageBox(utility::to_wstring(message, CP_UTF8), patch_notes_constants::successTitle, BaseDialogBox::messageBoxType::ok, dynamic_cast<gui_framework::BaseComponent*>(window)) == BaseDialogBox::messageBoxResponse::ok)
			{
				Initializer::get().createUI();
			}
		}
		else
		{
			BaseDialogBox::createMessageBox(utility::to_wstring(message, CP_UTF8), patch_notes_constants::errorTitle, BaseDialogBox::messageBoxType::ok, dynamic_cast<gui_framework::BaseComponent*>(window));
		}
	}
}
