#include "ProjectConfigurationController.h"

#include "Models/ProjectConfigurationModel.h"
#include "PatchNotesUtility.h"

using namespace std;

namespace controllers
{
	json::JSONBuilder ProjectConfigurationController::collectData(gui_framework::BaseComposite* window) const
	{
		uint32_t codepage = utility::getCodepage();
		json::JSONBuilder builder(codepage);

		string projectName = gui_framework::utility::to_string(dynamic_cast<gui_framework::EditControl*>(window->findChild(L"ProjectName"))->getText(), codepage);
		string projectVersion = gui_framework::utility::to_string(dynamic_cast<gui_framework::EditControl*>(window->findChild(L"ProjectVersion"))->getText(), codepage);

		if (projectName.empty())
		{
			throw runtime_error(R"(Поле "Название проекта" не может быть пустым)");
		}

		if (projectVersion.empty())
		{
			throw runtime_error(R"(Поле "Версия проекта" не может быть пустым)");
		}

		builder.
			append("projectName", move(projectName)).
			append("projectVersion", move(projectVersion));

		return builder;
	}

	ProjectConfigurationController::ProjectConfigurationController() :
		BaseController(shared_ptr<models::BaseModel>(new models::ProjectConfigurationModel()))
	{

	}
}
