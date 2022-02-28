#include "EditNoteController.h"

#include "ComponentsHeader.h"

#include "Models/Editing/EditNoteModel.h"
#include "PatchNotesUtility.h"

using namespace std;

namespace controllers
{
	json::JSONBuilder EditNoteController::collectData(gui_framework::BaseComposite* window) const
	{
		gui_framework::DropDownListComboBox* projects = static_cast<gui_framework::DropDownListComboBox*>(window->findChild(L"Projects"));
		gui_framework::DropDownListComboBox* categories = static_cast<gui_framework::DropDownListComboBox*>(window->findChild(L"Categories"));
		gui_framework::DropDownListComboBox* elements = static_cast<gui_framework::DropDownListComboBox*>(window->findChild(L"Elements"));
		gui_framework::DropDownListComboBox* notes = static_cast<gui_framework::DropDownListComboBox*>(window->findChild(L"Notes"));
		wstring newNote = static_cast<gui_framework::EditControl*>(window->findChild(L"NewNoteName"))->getText();
		string project = gui_framework::utility::to_string(projects->getValue(projects->getCurrentSelectionIndex()), CP_UTF8);
		string category = gui_framework::utility::to_string(categories->getValue(categories->getCurrentSelectionIndex()), CP_UTF8);
		string element = gui_framework::utility::to_string(elements->getValue(elements->getCurrentSelectionIndex()), CP_UTF8);
		string note = gui_framework::utility::to_string(notes->getValue(notes->getCurrentSelectionIndex()), CP_UTF8);

		return json::JSONBuilder(CP_UTF8).
			append("project", move(project)).
			append("category", move(category)).
			append("element", move(element)).
			append("note", move(note)).
			append("newNote", gui_framework::utility::to_string(newNote, CP_UTF8));
	}

	EditNoteController::EditNoteController() :
		BaseController(make_unique<models::EditNoteModel>())
	{

	}
}
