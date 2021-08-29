#include "DeleteProjectConfigurationController.h"

#include "Models/DeleteProjectConfigurationModel.h"

using namespace std;

namespace controllers
{
	json::JSONBuilder DeleteProjectConfigurationController::collectData(gui_framework::BaseComposite* window) const
	{
		return json::JSONBuilder(1251);
	}

	DeleteProjectConfigurationController::DeleteProjectConfigurationController() :
		BaseController(make_unique<models::DeleteProjectConfigurationModel>())
	{

	}
}
