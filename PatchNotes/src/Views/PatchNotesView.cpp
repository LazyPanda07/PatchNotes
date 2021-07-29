#include "PatchNotesView.h"

#include "Composites/ChildWindow.h"
#include "Components/ComboBoxes/DropDownListComboBox.h"
#include "Components/EditControl.h"
#include "Components/RichEdit.h"
#include "Components/Buttons/Button.h"

#include "PatchNotesConstants.h"
#include "PatchNotesUtility.h"

using namespace std;

CREATE_DEFAULT_WINDOW_FUNCTION(patchNotesUI)

namespace views
{
	gui_framework::BaseComposite* PatchNotesView::createPatchNotesWindow(const shared_ptr<controllers::BaseController>& controller, gui_framework::BaseComponent* parent)
	{
		using namespace gui_framework;

		uint16_t width = parent->getDesiredWidth();
		uint16_t height = parent->getDesiredHeight();

		gui_framework::utility::ComponentSettings settings(0, 0, width, height);
		ChildWindow* patchNotesWindow = new ChildWindow(L"PatchNotesUI", L"PatchNotesUI", settings, parent, "patchNotesUI");

		DropDownListComboBox* currentProject = new DropDownListComboBox(L"ProjectNameAndVersion", gui_framework::utility::ComponentSettings(width / 4, 0, width / 2, 20), patchNotesWindow);
		vector<wstring> projects = PatchNotesView::getAvailableProjectsFiles();

		currentProject->setAutoResize(false);

		for (const auto& i : projects)
		{
			currentProject->addValue(i);
		}

		if (projects.size())
		{
			currentProject->setCurrentSelection(0);
		}

		DropDownListComboBox* currentCategory = new DropDownListComboBox(L"ProjectCategory", gui_framework::utility::ComponentSettings(width / 4, 25, width / 2, 20), patchNotesWindow);
		vector<wstring> categories = PatchNotesView::getProjectCategories(currentProject->getValue(currentProject->getCurrentSelectionIndex()));

		for (const auto& i : categories)
		{
			currentCategory->addValue(i);
		}

		if (categories.size())
		{
			currentCategory->setCurrentSelection(0);
		}

		return patchNotesWindow;
	}

	vector<wstring> PatchNotesView::getAvailableProjectsFiles()
	{
		vector<wstring> result;
		map<filesystem::file_time_type, wstring> lastTimeModifiedFiles;

		filesystem::directory_iterator it(dataFolder);

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

		(pathToProject.append(dataFolder) /= projectName).append(".json");

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

	PatchNotesView::PatchNotesView(const shared_ptr<controllers::BaseController>& controller, gui_framework::BaseComponent* parent) :
		BaseView(controller, PatchNotesView::createPatchNotesWindow(controller, parent))
	{

	}

	void PatchNotesView::update(const json::JSONParser& data)
	{

	}
}
