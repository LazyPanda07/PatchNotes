#include "ProjectConfigurationController.h"

#include "ComponentsHeader.h"

#include "Models/ProjectConfigurationModel.h"
#include "PatchNotesUtility.h"
#include "Validation.h"

using namespace std;

namespace controllers
{
	json::JSONBuilder ProjectConfigurationController::collectData(gui_framework::BaseComposite* window) const
	{
		json::JSONBuilder builder(CP_UTF8);
		gui_framework::EditControl* projectNameEditControl = static_cast<gui_framework::EditControl*>(window->findChild(L"ProjectName"));
		gui_framework::EditControl* projectVersionEditControl = static_cast<gui_framework::EditControl*>(window->findChild(L"ProjectVersion"));
		string projectName = gui_framework::utility::to_string(projectNameEditControl->getText(), CP_UTF8);
		string projectVersion = gui_framework::utility::to_string(projectVersionEditControl->getText(), CP_UTF8);

		validation::emptyValidation(projectNameEditControl->getText(), projectNameEditControl->getPlaceholder());

		validation::emptyValidation(projectVersionEditControl->getText(), projectVersionEditControl->getPlaceholder());

		builder.
			append("projectName", move(projectName)).
			append("projectVersion", move(projectVersion));

		return builder;
	}

	ProjectConfigurationController::ProjectConfigurationController() :
		BaseController(make_unique<models::ProjectConfigurationModel>())
	{

	}
}
