#include "EditCategoryController.h"

#include "Models/Editing/EditCategoryModel.h"

using namespace std;

namespace controllers
{
	json::JSONBuilder EditCategoryController::collectData(gui_framework::BaseComposite* window) const
	{
		return json::JSONBuilder(1251);
	}

	EditCategoryController::EditCategoryController() :
		BaseController(make_unique<models::EditCategoryModel>())
	{

	}
}
