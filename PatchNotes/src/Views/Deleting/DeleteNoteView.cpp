#include "DeleteNoteView.h"

#include "Composites/DialogBox.h"

#include "Controllers/Deleting/DeleteNoteController.h"
#include "PatchNotesUtility.h"
#include "PatchNotesConstants.h"
#include "Initializer.h"

using namespace std;

CREATE_DEFAULT_WINDOW_FUNCTION(deleteNote)

namespace views
{
	gui_framework::BaseComposite* DeleteNoteView::createDeleteNoteDialog(const unique_ptr<controllers::BaseController>& controller)
	{
		using gui_framework::DialogBox;

		auto [x, y] = utility::getScreenCenter(gui_framework::standard_sizes::dialogBoxBuilderMinWidth, gui_framework::standard_sizes::dialogBoxBuilderMinHeight);

		DialogBox::DialogBoxBuilder builder(L"DeleteNote", localization::WTextLocalization::get()[patch_notes_localization::deleteNote], x, y, "deleteNote");

		gui_framework::utility::AdditionalCreationData<gui_framework::DropDownListComboBox> availableProjects(utility::getAvailableProjectsFiles());
		gui_framework::utility::AdditionalCreationData<gui_framework::Button> confirm(localization::WTextLocalization::get()[patch_notes_localization::deleteButton], []() {});

		builder.
			addComponent<gui_framework::DropDownListComboBox>(L"AvailableProjects", 200, 25, DialogBox::DialogBoxBuilder::alignment::center, availableProjects).
			addComponent<gui_framework::DropDownListComboBox>(L"AvailableCategories", 200, 25, DialogBox::DialogBoxBuilder::alignment::center).
			addComponent<gui_framework::DropDownListComboBox>(L"AvailableElements", 200, 25, DialogBox::DialogBoxBuilder::alignment::center).
			addComponent<gui_framework::DropDownListComboBox>(L"NoteToDelete", 200, 25, DialogBox::DialogBoxBuilder::alignment::center).
			addComponent<gui_framework::Button>(L"ConfirmDeleteNote", 200, 20, DialogBox::DialogBoxBuilder::alignment::center, confirm);

		DialogBox* result = builder.build();
		gui_framework::DropDownListComboBox* categories = static_cast<gui_framework::DropDownListComboBox*>(result->findChild(L"AvailableCategories"));
		gui_framework::DropDownListComboBox* elements = static_cast<gui_framework::DropDownListComboBox*>(result->findChild(L"AvailableElements"));
		gui_framework::DropDownListComboBox* notes = static_cast<gui_framework::DropDownListComboBox*>(result->findChild(L"NoteToDelete"));

		static_cast<gui_framework::DropDownListComboBox*>(result->findChild(L"AvailableProjects"))->setOnSelectionChange([categories](gui_framework::BaseComboBox& current)
			{
				if (current.getCurrentSelectionIndex() == -1)
				{
					return;
				}

				categories->clear();
				vector<wstring> findedCategories = utility::getAvailableCategories(current.getValue(current.getCurrentSelectionIndex()));

				for (const auto& i : findedCategories)
				{
					categories->addValue(i);
				}
			});

		categories->setOnSelectionChange([elements, result](gui_framework::BaseComboBox& current)
			{
				if (current.getCurrentSelectionIndex() == -1)
				{
					return;
				}

				elements->clear();
				gui_framework::DropDownListComboBox* projects = static_cast<gui_framework::DropDownListComboBox*>(result->findChild(L"AvailableProjects"));
				vector<wstring> findedElements = utility::getAvailableElements(projects->getValue(projects->getCurrentSelectionIndex()), current.getValue(current.getCurrentSelectionIndex()));

				for (const auto& i : findedElements)
				{
					elements->addValue(i);
				}
			});

		elements->setOnSelectionChange([result, notes](gui_framework::BaseComboBox& current)
			{
				if (current.getCurrentSelectionIndex() == -1)
				{
					return;
				}

				notes->clear();
				gui_framework::DropDownListComboBox* projects = static_cast<gui_framework::DropDownListComboBox*>(result->findChild(L"AvailableProjects"));
				gui_framework::DropDownListComboBox* categories = static_cast<gui_framework::DropDownListComboBox*>(result->findChild(L"AvailableCategories"));
				vector<wstring> findedNotes = utility::getAvailableNotes(projects->getValue(projects->getCurrentSelectionIndex()), categories->getValue(categories->getCurrentSelectionIndex()), current.getValue(current.getCurrentSelectionIndex()));

				for (const auto& i : findedNotes)
				{
					notes->addValue(i);
				}
			});

		static_cast<gui_framework::Button*>(result->findChild(L"ConfirmDeleteNote"))->setOnClick([&controller, result]()
			{
				if (static_cast<gui_framework::DropDownListComboBox*>(result->findChild(L"AvailableProjects"))->getCurrentSelectionIndex() == -1)
				{
					return;
				}

				if (static_cast<gui_framework::DropDownListComboBox*>(result->findChild(L"AvailableCategories"))->getCurrentSelectionIndex() == -1)
				{
					return;
				}

				if (static_cast<gui_framework::DropDownListComboBox*>(result->findChild(L"AvailableElements"))->getCurrentSelectionIndex() == -1)
				{
					return;
				}

				if (static_cast<gui_framework::DropDownListComboBox*>(result->findChild(L"NoteToDelete"))->getCurrentSelectionIndex() == -1)
				{
					return;
				}

				controller->receiveData(result);
			});

		result->show();

		return result;
	}

	DeleteNoteView::DeleteNoteView() :
		BaseView(make_unique<controllers::DeleteNoteController>(), DeleteNoteView::createDeleteNoteDialog(controller))
	{

	}

	void DeleteNoteView::update(const json::JSONParser& data)
	{
		using gui_framework::BaseDialogBox;

		bool success = data.getBool("success");
		string message = data.getString("message");
		const wstring& title = success ? patch_notes_constants::successTitle : patch_notes_constants::errorTitle;

		if (BaseDialogBox::createMessageBox(utility::to_wstring(message, CP_UTF8), title, BaseDialogBox::messageBoxType::ok, static_cast<gui_framework::BaseComponent*>(window)) == BaseDialogBox::messageBoxResponse::ok)
		{
			Initializer::get().createUI();

			Initializer::get().closeDeleteNote();
		}
	}
}
