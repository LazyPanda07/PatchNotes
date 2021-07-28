#include "PatchNotesView.h"

#include "Composites/ChildWindow.h"
#include "Components/ComboBoxes/DropDownListComboBox.h"
#include "Components/EditControl.h"
#include "Components/RichEdit.h"
#include "Components/Buttons/Button.h"

#include "PatchNotesConstants.h"

using namespace std;

CREATE_DEFAULT_WINDOW_FUNCTION(patchNotesUI)

namespace views
{
	gui_framework::BaseComposite* PatchNotesView::createPatchNotesWindow(const shared_ptr<controllers::BaseController>& controller, gui_framework::BaseComponent* parent)
	{
		using namespace gui_framework;

		uint16_t width = parent->getDesiredWidth();
		uint16_t height = parent->getDesiredHeight();

		utility::ComponentSettings settings(0, 0, width, height);
		ChildWindow* patchNotesWindow = new ChildWindow(L"PatchNotesUI", L"PatchNotesUI", settings, parent, "patchNotesUI");

		DropDownListComboBox* currentProject = new DropDownListComboBox(L"ProjectNameAndVersion", settings, patchNotesWindow);
		vector<wstring> currentProjectValues = PatchNotesView::getAvailableProjectsFiles();

		currentProject->setAutoResize(false);

		for (const auto& i : currentProjectValues)
		{
			currentProject->addValue(i);
		}

		currentProject->setCurrentSelection(0);

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

	PatchNotesView::PatchNotesView(const shared_ptr<controllers::BaseController>& controller, gui_framework::BaseComponent* parent) :
		BaseView(controller, PatchNotesView::createPatchNotesWindow(controller, parent))
	{

	}

	void PatchNotesView::update(const json::JSONParser& data)
	{

	}
}
