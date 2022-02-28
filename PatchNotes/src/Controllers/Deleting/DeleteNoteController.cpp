#include "DeleteNoteController.h"

#include "ComponentsHeader.h"

#include "Models/Deleting/DeleteNoteModel.h"
#include "PatchNotesUtility.h"
#include "PatchNotesConstants.h"

using namespace std;

namespace controllers
{
	json::JSONBuilder DeleteNoteController::collectData(gui_framework::BaseComposite* window) const
	{
		json::JSONBuilder builder(CP_UTF8);
		gui_framework::DropDownListComboBox* projectsList = static_cast<gui_framework::DropDownListComboBox*>(window->findChild(L"AvailableProjects"));
		gui_framework::DropDownListComboBox* categoriesList = static_cast<gui_framework::DropDownListComboBox*>(window->findChild(L"AvailableCategories"));
		gui_framework::DropDownListComboBox* elementsList = static_cast<gui_framework::DropDownListComboBox*>(window->findChild(L"AvailableElements"));
		gui_framework::DropDownListComboBox* notesList = static_cast<gui_framework::DropDownListComboBox*>(window->findChild(L"NoteToDelete"));
		string pathToProjectToDelete = globals::dataFolder + '\\' + gui_framework::utility::to_string(projectsList->getValue(projectsList->getCurrentSelectionIndex()), CP_UTF8) + ".json";

		ranges::replace(pathToProjectToDelete, '\\', '/');

		builder.
			append("pathToProject"s, move(pathToProjectToDelete)).
			append("category"s, gui_framework::utility::to_string(categoriesList->getValue(categoriesList->getCurrentSelectionIndex()), CP_UTF8)).
			append("element"s, gui_framework::utility::to_string(elementsList->getValue(elementsList->getCurrentSelectionIndex()), CP_UTF8)).
			append("noteToDelete"s, gui_framework::utility::to_string(notesList->getValue(notesList->getCurrentSelectionIndex()), CP_UTF8));

		return builder;
	}

	DeleteNoteController::DeleteNoteController() :
		BaseController(make_unique<models::DeleteNoteModel>())
	{

	}
}
