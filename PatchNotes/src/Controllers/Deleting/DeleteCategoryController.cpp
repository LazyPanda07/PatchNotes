#include "DeleteCategoryController.h"

#include "Models/Deleting/DeleteCategoryModel.h"
#include "PatchNotesUtility.h"
#include "PatchNotesConstants.h"

using namespace std;

namespace controllers
{
	json::JSONBuilder DeleteCategoryController::collectData(gui_framework::BaseComposite* window) const
	{
		uint32_t codepage = utility::getCodepage();
		json::JSONBuilder builder(codepage);
		gui_framework::DropDownListComboBox* projectsList = static_cast<gui_framework::DropDownListComboBox*>(window->findChild(L"AvailableProjects"));
		gui_framework::DropDownListComboBox* categoriesList = static_cast<gui_framework::DropDownListComboBox*>(window->findChild(L"CategoryToDelete"));
		string pathToProjectToDelete = globals::dataFolder + '\\' + gui_framework::utility::to_string(projectsList->getValue(projectsList->getCurrentSelectionIndex()), codepage) + ".json";

		ranges::replace(pathToProjectToDelete, '\\', '/');

		builder.
			append("pathToProject"s, move(pathToProjectToDelete)).
			append("categoryToDelete"s, gui_framework::utility::to_string(categoriesList->getValue(categoriesList->getCurrentSelectionIndex()), codepage));

		return builder;
	}

	DeleteCategoryController::DeleteCategoryController() :
		BaseController(make_unique<models::DeleteCategoryModel>())
	{

	}
}
