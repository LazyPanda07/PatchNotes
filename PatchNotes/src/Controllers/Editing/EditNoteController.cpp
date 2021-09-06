#include "EditNoteController.h"

#include "Models/Editing/EditNoteModel.h"
#include "PatchNotesUtility.h"

using namespace std;

namespace controllers
{
	json::JSONBuilder EditNoteController::collectData(gui_framework::BaseComposite* window) const
	{
		uint32_t codepage = utility::getCodepage();
		gui_framework::DropDownListComboBox* projects = static_cast<gui_framework::DropDownListComboBox*>(window->findChild(L"Projects"));
		gui_framework::DropDownListComboBox* categories = static_cast<gui_framework::DropDownListComboBox*>(window->findChild(L"Categories"));
		gui_framework::DropDownListComboBox* elements = static_cast<gui_framework::DropDownListComboBox*>(window->findChild(L"Elements"));
		gui_framework::DropDownListComboBox* notes = static_cast<gui_framework::DropDownListComboBox*>(window->findChild(L"Notes"));
		wstring newNote = static_cast<gui_framework::EditControl*>(window->findChild(L"NewNoteName"))->getText();
		string project = gui_framework::utility::to_string(projects->getValue(projects->getCurrentSelectionIndex()), codepage);
		string category = gui_framework::utility::to_string(categories->getValue(categories->getCurrentSelectionIndex()), codepage);
		string element = gui_framework::utility::to_string(elements->getValue(elements->getCurrentSelectionIndex()), codepage);
		string note = gui_framework::utility::to_string(notes->getValue(notes->getCurrentSelectionIndex()), codepage);

		return json::JSONBuilder(codepage).
			append("project", move(project)).
			append("category", move(category)).
			append("element", move(element)).
			append("note", move(note)).
			append("newNote", gui_framework::utility::to_string(newNote, codepage));
	}

	EditNoteController::EditNoteController() :
		BaseController(make_unique<models::EditNoteModel>())
	{

	}
}
