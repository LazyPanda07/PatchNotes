#include "DeleteCategoryController.h"

#include "ComponentsHeader.h"

#include "Models/Deleting/DeleteCategoryModel.h"
#include "PatchNotesUtility.h"
#include "PatchNotesConstants.h"

using namespace std;

namespace controllers
{
	json::JSONBuilder DeleteCategoryController::collectData(gui_framework::BaseComposite* window) const
	{
		json::JSONBuilder builder(CP_UTF8);
		gui_framework::DropDownListComboBox* projectsList = static_cast<gui_framework::DropDownListComboBox*>(window->findChild(L"AvailableProjects"));
		gui_framework::DropDownListComboBox* categoriesList = static_cast<gui_framework::DropDownListComboBox*>(window->findChild(L"CategoryToDelete"));
		string pathToProjectToDelete = globals::dataFolder + '\\' + gui_framework::utility::to_string(projectsList->getValue(projectsList->getCurrentSelectionIndex()), CP_UTF8) + ".json";

		ranges::replace(pathToProjectToDelete, '\\', '/');

		builder.
			append("pathToProject"s, move(pathToProjectToDelete)).
			append("categoryToDelete"s, gui_framework::utility::to_string(categoriesList->getValue(categoriesList->getCurrentSelectionIndex()), CP_UTF8));

		return builder;
	}

	DeleteCategoryController::DeleteCategoryController() :
		BaseController(make_unique<models::DeleteCategoryModel>())
	{

	}
}
