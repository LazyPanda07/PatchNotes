#include "ProjectConfigurationController.h"

#include "Models/ProjectConfigurationModel.h"
#include "PatchNotesUtility.h"
#include "Validation.h"

using namespace std;

namespace controllers
{
	json::JSONBuilder ProjectConfigurationController::collectData(gui_framework::BaseComposite* window) const
	{
		uint32_t codepage = utility::getCodepage();
		json::JSONBuilder builder(codepage);
		gui_framework::EditControl* projectNameEditControl = static_cast<gui_framework::EditControl*>(window->findChild(L"ProjectName"));
		gui_framework::EditControl* projectVersionEditControl = static_cast<gui_framework::EditControl*>(window->findChild(L"ProjectVersion"));
		string projectName = gui_framework::utility::to_string(projectNameEditControl->getText(), codepage);
		string projectVersion = gui_framework::utility::to_string(projectVersionEditControl->getText(), codepage);

		validation::emptyValidation(projectName, projectNameEditControl->getPlaceholder());

		validation::emptyValidation(projectVersion, projectVersionEditControl->getPlaceholder());

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
