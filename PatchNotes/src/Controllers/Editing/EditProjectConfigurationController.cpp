#include "EditProjectConfigurationController.h"

#include "Models/Editing/EditProjectConfigurationModel.h"

using namespace std;

namespace controllers
{
	json::JSONBuilder EditProjectConfigurationController::collectData(gui_framework::BaseComposite* window) const
	{
		return json::JSONBuilder(1251);
	}

	EditProjectConfigurationController::EditProjectConfigurationController() :
		BaseController(make_unique<models::EditProjectConfigurationModel>())
	{

	}
}
