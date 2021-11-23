#include "PatchNotesController.h"

#include "headers.h"

#include "Models/PatchNotesModel.h"
#include "PatchNotesUtility.h"
#include "Validation.h"
#include "PatchNotesConstants.h"

#include "Exceptions/ValidationException.h"

#pragma warning(disable: 26800)

using namespace std;

namespace controllers
{
	json::JSONBuilder PatchNotesController::collectData(gui_framework::BaseComposite* window) const
	{
		json::JSONBuilder builder(CP_UTF8);
		gui_framework::DropDownListComboBox* currentProject = static_cast<gui_framework::DropDownListComboBox*>(window->findChild(L"ProjectNameAndVersion"));
		gui_framework::DropDownListComboBox* currentCategory = static_cast<gui_framework::DropDownListComboBox*>(window->findChild(L"ProjectCategory"));
		string item = gui_framework::utility::to_string(static_cast<gui_framework::EditControl*>(window->findChild(L"Item"))->getText(), CP_UTF8);
		wstring textNotes = static_cast<gui_framework::RichEdit*>(window->findChild(L"Notes"))->getText();
		localization::WTextLocalization& textLocalization = localization::WTextLocalization::get();

		if (currentProject->getCurrentSelectionIndex() == -1)
		{
			throw exceptions::ValidationException(textLocalization[patch_notes_localization::failedToFindProject]);
		}

		if (currentCategory->getCurrentSelectionIndex() == -1)
		{
			throw exceptions::ValidationException(textLocalization[patch_notes_localization::failedToFindCategory]);
		}

		validation::emptyValidation(static_cast<gui_framework::EditControl*>(window->findChild(L"Item"))->getText(), static_cast<gui_framework::EditControl*>(window->findChild(L"Element"))->getPlaceholder());

		validation::emptyValidation(textNotes, textLocalization[patch_notes_localization::notes]);

		istringstream is(gui_framework::utility::to_string(textNotes, CP_UTF8));
		string tem;
		vector<json::utility::objectSmartPointer<json::utility::jsonObject>> notes;

		while (getline(is, tem))
		{
			erase(tem, '\r');

			json::utility::appendArray(move(tem), notes);
		}

		builder.
			append("projectFile", gui_framework::utility::to_string(currentProject->getValue(currentProject->getCurrentSelectionIndex()), CP_UTF8)).
			append("category", gui_framework::utility::to_string(currentCategory->getValue(currentCategory->getCurrentSelectionIndex()), CP_UTF8)).
			append("item", move(item)).
			append("notes", move(notes));

		return builder;
	}

	PatchNotesController::PatchNotesController() :
		BaseController(make_unique<models::PatchNotesModel>())
	{

	}
}
