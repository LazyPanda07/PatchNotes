#include "EditCategoryController.h"

#include "ComponentsHeader.h"

#include "Models/Editing/EditCategoryModel.h"
#include "PatchNotesUtility.h"

using namespace std;

namespace controllers
{
	json::JSONBuilder EditCategoryController::collectData(gui_framework::BaseComposite* window) const
	{
		gui_framework::DropDownListComboBox* projects = static_cast<gui_framework::DropDownListComboBox*>(window->findChild(L"Projects"));
		gui_framework::DropDownListComboBox* categories = static_cast<gui_framework::DropDownListComboBox*>(window->findChild(L"Categories"));
		wstring newCategory = static_cast<gui_framework::EditControl*>(window->findChild(L"NewCategoryName"))->getText();
		string project = gui_framework::utility::to_string(projects->getValue(projects->getCurrentSelectionIndex()), CP_UTF8);
		string category = gui_framework::utility::to_string(categories->getValue(categories->getCurrentSelectionIndex()), CP_UTF8);

		return json::JSONBuilder(CP_UTF8).
			append("project", move(project)).
			append("category", move(category)).
			append("newCategory", gui_framework::utility::to_string(newCategory, CP_UTF8));
	}

	EditCategoryController::EditCategoryController() :
		BaseController(make_unique<models::EditCategoryModel>())
	{

	}
}
