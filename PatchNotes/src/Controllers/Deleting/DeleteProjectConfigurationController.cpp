#include "DeleteProjectConfigurationController.h"

#include "ComponentsHeader.h"

#include "Models/Deleting/DeleteProjectConfigurationModel.h"
#include "PatchNotesUtility.h"
#include "PatchNotesConstants.h"

using namespace std;

namespace controllers
{
	json::JSONBuilder DeleteProjectConfigurationController::collectData(gui_framework::BaseComposite* window) const
	{
		json::JSONBuilder builder(CP_UTF8);
		gui_framework::DropDownListComboBox* list = static_cast<gui_framework::DropDownListComboBox*>(window->findChild(L"ProjectsToDelete"));
		string pathToProjectToDelete = globals::dataFolder + '\\' + gui_framework::utility::to_string(list->getValue(list->getCurrentSelectionIndex()), CP_UTF8) + ".json";

		ranges::replace(pathToProjectToDelete, '\\', '/');

		builder.
			append("projectToDelete"s, move(pathToProjectToDelete));

		return builder;
	}

	DeleteProjectConfigurationController::DeleteProjectConfigurationController() :
		BaseController(make_unique<models::DeleteProjectConfigurationModel>())
	{

	}
}
