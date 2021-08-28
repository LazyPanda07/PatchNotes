#include "PatchNotesController.h"

#include "headers.h"

#include "Models/PatchNotesModel.h"
#include "PatchNotesUtility.h"
#include "Validation.h"

#include "Exceptions/ValidationException.h"

using namespace std;

namespace controllers
{
	json::JSONBuilder PatchNotesController::collectData(gui_framework::BaseComposite* window) const
	{
		uint32_t codepage = utility::getCodepage();
		json::JSONBuilder builder(codepage);
		gui_framework::DropDownListComboBox* currentProject = dynamic_cast<gui_framework::DropDownListComboBox*>(window->findChild(L"ProjectNameAndVersion"));
		gui_framework::DropDownListComboBox* currentCategory = dynamic_cast<gui_framework::DropDownListComboBox*>(window->findChild(L"ProjectCategory"));
		string item = gui_framework::utility::to_string(dynamic_cast<gui_framework::EditControl*>(window->findChild(L"Item"))->getText(), codepage);
		wstring textNotes = dynamic_cast<gui_framework::RichEdit*>(window->findChild(L"Notes"))->getText();

		if (currentProject->getCurrentSelectionIndex() == -1)
		{
			throw exceptions::ValidationException("Не удалось определить проект");
		}

		if (currentCategory->getCurrentSelectionIndex() == -1)
		{
			throw exceptions::ValidationException("Не удалось определить категорию");
		}

		validation::emptyValidation(item, dynamic_cast<gui_framework::EditControl*>(window->findChild(L"Element"))->getPlaceholder());

		validation::emptyValidation(textNotes, L"Примечания");

		istringstream is(gui_framework::utility::to_string(textNotes, codepage));
		string tem;
		vector<json::utility::objectSmartPointer<json::utility::jsonObject>> notes;

		while (getline(is, tem))
		{
			erase(tem, '\r');

			json::utility::appendArray(move(tem), notes);
		}

		builder.
			append("projectFile", gui_framework::utility::to_string(currentProject->getValue(currentProject->getCurrentSelectionIndex()), codepage)).
			append("category", gui_framework::utility::to_string(currentCategory->getValue(currentCategory->getCurrentSelectionIndex()), codepage)).
			append("item", move(item)).
			append("notes", move(notes));

		return builder;
	}

	PatchNotesController::PatchNotesController() :
		BaseController(make_unique<models::PatchNotesModel>())
	{

	}
}
