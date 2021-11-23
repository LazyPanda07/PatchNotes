#include "CategoryController.h"

#include "Models/CategoryModel.h"
#include "PatchNotesUtility.h"
#include "Validation.h"

using namespace std;

namespace controllers
{
	json::JSONBuilder CategoryController::collectData(gui_framework::BaseComposite* window) const
	{
		json::JSONBuilder builder(CP_UTF8);
		gui_framework::EditControl* categoryEditControl = static_cast<gui_framework::EditControl*>(window->findChild(L"CategoryName"));
		string projectFile = gui_framework::utility::to_string(static_cast<gui_framework::StaticControl*>(window->findChild(L"ProjectCategory"))->getText(), CP_UTF8);
		string categoryName = gui_framework::utility::to_string(categoryEditControl->getText(), CP_UTF8);

		validation::emptyValidation(categoryEditControl->getText(), categoryEditControl->getPlaceholder());

		builder.
			append("projectFile", move(projectFile)).
			append("category", move(categoryName));

		return builder;
	}

	CategoryController::CategoryController() :
		BaseController(make_unique<models::CategoryModel>())
	{

	}
}
