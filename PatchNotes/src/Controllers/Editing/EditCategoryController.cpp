#include "EditCategoryController.h"

#include "Models/Editing/EditCategoryModel.h"
#include "PatchNotesUtility.h"

using namespace std;

namespace controllers
{
	json::JSONBuilder EditCategoryController::collectData(gui_framework::BaseComposite* window) const
	{
		uint32_t codepage = utility::getCodepage();
		gui_framework::DropDownListComboBox* projects = static_cast<gui_framework::DropDownListComboBox*>(window->findChild(L"Projects"));
		gui_framework::DropDownListComboBox* categories = static_cast<gui_framework::DropDownListComboBox*>(window->findChild(L"Categories"));
		const wstring& newCategory = static_cast<gui_framework::EditControl*>(window->findChild(L"NewCategoryName"))->getText();
		string project = gui_framework::utility::to_string(projects->getValue(projects->getCurrentSelectionIndex()), codepage);
		string category = gui_framework::utility::to_string(categories->getValue(categories->getCurrentSelectionIndex()), codepage);

		return json::JSONBuilder(codepage).
			append("project", move(project)).
			append("category", move(category)).
			append("newCategory", gui_framework::utility::to_string(newCategory, codepage));
	}

	EditCategoryController::EditCategoryController() :
		BaseController(make_unique<models::EditCategoryModel>())
	{

	}
}
