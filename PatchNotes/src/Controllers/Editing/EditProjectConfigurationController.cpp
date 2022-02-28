#include "EditProjectConfigurationController.h"

#include "ComponentsHeader.h"

#include "Models/Editing/EditProjectConfigurationModel.h"
#include "PatchNotesUtility.h"

using namespace std;

namespace controllers
{
	json::JSONBuilder EditProjectConfigurationController::collectData(gui_framework::BaseComposite* window) const
	{
		gui_framework::DropDownComboBox* projects = static_cast<gui_framework::DropDownComboBox*>(window->findChild(L"ProjectsToEdit"));
		string projectToEdit = gui_framework::utility::to_string(projects->getValue(projects->getCurrentSelectionIndex()), CP_UTF8);
		string newProjectName = gui_framework::utility::to_string(static_cast<gui_framework::EditControl*>(window->findChild(L"NewConfigurationName"))->getText(), CP_UTF8);
		string newProjectVersion = gui_framework::utility::to_string(static_cast<gui_framework::EditControl*>(window->findChild(L"NewConfigurationVersion"))->getText(), CP_UTF8);

		return json::JSONBuilder(CP_UTF8).
			append("projectToEdit", move(projectToEdit)).
			append("newProjectName", move(newProjectName)).
			append("newProjectVersion", move(newProjectVersion));;
	}

	EditProjectConfigurationController::EditProjectConfigurationController() :
		BaseController(make_unique<models::EditProjectConfigurationModel>())
	{

	}
}
