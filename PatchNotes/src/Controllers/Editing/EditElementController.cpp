#include "EditElementController.h"

#include "Models/Editing/EditElementModel.h"

using namespace std;

namespace controllers
{
	json::JSONBuilder EditElementController::collectData(gui_framework::BaseComposite* window) const
	{
		return json::JSONBuilder(1251);
	}

	EditElementController::EditElementController() :
		BaseController(make_unique<models::EditElementModel>())
	{

	}
}
