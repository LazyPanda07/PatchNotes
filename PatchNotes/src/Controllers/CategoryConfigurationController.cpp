#include "CategoryConfigurationController.h"

#include "Models/CategoryConfigurationModel.h"
#include "PatchNotesUtility.h"

using namespace std;

namespace controllers
{
	json::JSONBuilder CategoryConfigurationController::collectData(gui_framework::BaseComposite* window) const
	{
		json::JSONBuilder builder(utility::getCodepage());



		return builder;
	}

	CategoryConfigurationController::CategoryConfigurationController() :
		BaseController(make_shared<models::CategoryConfigurationModel>())
	{

	}
}
