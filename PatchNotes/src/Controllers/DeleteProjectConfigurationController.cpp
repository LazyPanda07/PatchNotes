#include "DeleteProjectConfigurationController.h"

#include "Models/DeleteProjectConfigurationModel.h"
#include "PatchNotesUtility.h"
#include "PatchNotesConstants.h"

using namespace std;

namespace controllers
{
	json::JSONBuilder DeleteProjectConfigurationController::collectData(gui_framework::BaseComposite* window) const
	{
		uint32_t codepage = utility::getCodepage();
		json::JSONBuilder builder(codepage);
		gui_framework::DropDownListComboBox* list = static_cast<gui_framework::DropDownListComboBox*>(window->findChild(L"ProjectsToDelete"));
		string pathToProjectToDelete = globals::dataFolder + '\\' + gui_framework::utility::to_string(list->getValue(list->getCurrentSelectionIndex()), codepage) + ".json";

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
