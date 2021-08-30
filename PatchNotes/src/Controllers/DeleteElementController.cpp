#include "DeleteElementController.h"

#include "Models/DeleteElementModel.h"
#include "PatchNotesUtility.h"
#include "PatchNotesConstants.h"

using namespace std;

namespace controllers
{
	json::JSONBuilder DeleteElementController::collectData(gui_framework::BaseComposite* window) const
	{
		uint32_t codepage = utility::getCodepage();
		json::JSONBuilder builder(codepage);
		gui_framework::DropDownListComboBox* projectsList = static_cast<gui_framework::DropDownListComboBox*>(window->findChild(L"AvailableProjects"));
		gui_framework::DropDownListComboBox* categoriesList = static_cast<gui_framework::DropDownListComboBox*>(window->findChild(L"AvailableCategories"));
		gui_framework::DropDownListComboBox* elementsList = static_cast<gui_framework::DropDownListComboBox*>(window->findChild(L"ElementToDelete"));
		string pathToProjectToDelete = globals::dataFolder + '\\' + gui_framework::utility::to_string(projectsList->getValue(projectsList->getCurrentSelectionIndex()), codepage) + ".json";

		ranges::replace(pathToProjectToDelete, '\\', '/');

		builder.
			append("pathToProject"s, move(pathToProjectToDelete)).
			append("category"s, gui_framework::utility::to_string(categoriesList->getValue(categoriesList->getCurrentSelectionIndex()), codepage)).
			append("elementToDelete"s, gui_framework::utility::to_string(elementsList->getValue(elementsList->getCurrentSelectionIndex()), codepage));

		return builder;
	}

	DeleteElementController::DeleteElementController() :
		BaseController(make_unique<models::DeleteElementModel>())
	{

	}
}
