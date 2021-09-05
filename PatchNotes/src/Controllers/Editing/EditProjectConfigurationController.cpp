#include "EditProjectConfigurationController.h"

#include "Models/Editing/EditProjectConfigurationModel.h"
#include "PatchNotesUtility.h"

using namespace std;

namespace controllers
{
	json::JSONBuilder EditProjectConfigurationController::collectData(gui_framework::BaseComposite* window) const
	{
		uint32_t codepage = utility::getCodepage();
		gui_framework::DropDownComboBox* projects = static_cast<gui_framework::DropDownComboBox*>(window->findChild(L"ProjectsToEdit"));
		string projectToEdit = gui_framework::utility::to_string(projects->getValue(projects->getCurrentSelectionIndex()), codepage);
		string newProjectName = gui_framework::utility::to_string(static_cast<gui_framework::EditControl*>(window->findChild(L"NewConfigurationName"))->getText(), codepage);
		string newProjectVersion = gui_framework::utility::to_string(static_cast<gui_framework::EditControl*>(window->findChild(L"NewConfigurationVersion"))->getText(), codepage);

		return json::JSONBuilder(codepage).
			append("projectToEdit", move(projectToEdit)).
			append("newProjectName", move(newProjectName)).
			append("newProjectVersion", move(newProjectVersion));;
	}

	EditProjectConfigurationController::EditProjectConfigurationController() :
		BaseController(make_unique<models::EditProjectConfigurationModel>())
	{

	}
}
