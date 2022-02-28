#include "DeleteElementController.h"

#include "ComponentsHeader.h"

#include "Models/Deleting/DeleteElementModel.h"
#include "PatchNotesUtility.h"
#include "PatchNotesConstants.h"

using namespace std;

namespace controllers
{
	json::JSONBuilder DeleteElementController::collectData(gui_framework::BaseComposite* window) const
	{
		json::JSONBuilder builder(CP_UTF8);
		gui_framework::DropDownListComboBox* projectsList = static_cast<gui_framework::DropDownListComboBox*>(window->findChild(L"AvailableProjects"));
		gui_framework::DropDownListComboBox* categoriesList = static_cast<gui_framework::DropDownListComboBox*>(window->findChild(L"AvailableCategories"));
		gui_framework::DropDownListComboBox* elementsList = static_cast<gui_framework::DropDownListComboBox*>(window->findChild(L"ElementToDelete"));
		string pathToProjectToDelete = globals::dataFolder + '\\' + gui_framework::utility::to_string(projectsList->getValue(projectsList->getCurrentSelectionIndex()), CP_UTF8) + ".json";

		ranges::replace(pathToProjectToDelete, '\\', '/');

		builder.
			append("pathToProject"s, move(pathToProjectToDelete)).
			append("category"s, gui_framework::utility::to_string(categoriesList->getValue(categoriesList->getCurrentSelectionIndex()), CP_UTF8)).
			append("elementToDelete"s, gui_framework::utility::to_string(elementsList->getValue(elementsList->getCurrentSelectionIndex()), CP_UTF8));

		return builder;
	}

	DeleteElementController::DeleteElementController() :
		BaseController(make_unique<models::DeleteElementModel>())
	{

	}
}
