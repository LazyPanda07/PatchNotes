#include "EditNoteView.h"

#include "Composites/DialogBox.h"

#include "Controllers/Editing/EditNoteController.h"
#include "PatchNotesUtility.h"
#include "PatchNotesConstants.h"
#include "Initializer.h"

using namespace std;

CREATE_DEFAULT_WINDOW_FUNCTION(editNote)

namespace views
{
	gui_framework::BaseComposite* EditNoteView::createEditNoteDialog(const std::unique_ptr<controllers::BaseController>& controller)
	{
		using gui_framework::DialogBox;

		auto [x, y] = utility::getScreenCenter(gui_framework::standard_sizes::dialogBoxBuilderMinWidth, gui_framework::standard_sizes::dialogBoxBuilderMinHeight);

		DialogBox::DialogBoxBuilder builder(L"EditNote", localization::WTextLocalization::get()[patch_notes_localization::editNote], x, y, "editNote");

		gui_framework::utility::AdditionalCreationData<gui_framework::DropDownListComboBox> projects(utility::getAvailableProjectsFiles());
		gui_framework::utility::AdditionalCreationData<gui_framework::EditControl> newNoteName(localization::WTextLocalization::get()[patch_notes_localization::newNoteName]);
		gui_framework::utility::AdditionalCreationData<gui_framework::Button> confirm(localization::WTextLocalization::get()[patch_notes_localization::editButton], []() {});

		builder.
			addComponent<gui_framework::DropDownListComboBox>(L"Projects", 300, 25, DialogBox::DialogBoxBuilder::alignment::center, projects).
			addComponent<gui_framework::DropDownListComboBox>(L"Categories", 300, 25, DialogBox::DialogBoxBuilder::alignment::center).
			addComponent<gui_framework::DropDownListComboBox>(L"Elements", 300, 25, DialogBox::DialogBoxBuilder::alignment::center).
			addComponent<gui_framework::DropDownListComboBox>(L"Notes", 300, 25, DialogBox::DialogBoxBuilder::alignment::center).
			addComponent<gui_framework::EditControl>(L"NewNoteName", 300, 20, DialogBox::DialogBoxBuilder::alignment::center, newNoteName).
			addComponent<gui_framework::Button>(L"ConfirmEditNote", 300, 20, DialogBox::DialogBoxBuilder::alignment::center, confirm);

		DialogBox* result = builder.build();
		gui_framework::DropDownListComboBox* projectsList = static_cast<gui_framework::DropDownListComboBox*>(result->findChild(L"Projects"));
		gui_framework::DropDownListComboBox* categoriesList = static_cast<gui_framework::DropDownListComboBox*>(result->findChild(L"Categories"));
		gui_framework::DropDownListComboBox* elementsList = static_cast<gui_framework::DropDownListComboBox*>(result->findChild(L"Elements"));
		gui_framework::DropDownListComboBox* notesList = static_cast<gui_framework::DropDownListComboBox*>(result->findChild(L"Notes"));

		static_cast<gui_framework::Button*>(result->findChild(L"ConfirmEditNote"))->setOnClick([&controller, result]()
			{
				if (static_cast<gui_framework::DropDownListComboBox*>(result->findChild(L"Projects"))->getCurrentSelectionIndex() == -1)
				{
					return;
				}
				else if (static_cast<gui_framework::EditControl*>(result->findChild(L"NewNoteName"))->getText().empty())
				{
					return;
				}

				controller->receiveData(result);
			});

		projectsList->setOnSelectionChange([categoriesList](gui_framework::BaseComboBox& current)
			{
				if (current.getCurrentSelectionIndex() == -1)
				{
					return;
				}

				categoriesList->clear();
				vector<wstring> findedCategories = utility::getAvailableCategories(current.getValue(current.getCurrentSelectionIndex()));

				for (const auto& i : findedCategories)
				{
					categoriesList->addValue(i);
				}
			});

		categoriesList->setOnSelectionChange([projectsList, elementsList](gui_framework::BaseComboBox& current)
			{
				if (current.getCurrentSelectionIndex() == -1)
				{
					return;
				}

				elementsList->clear();
				vector<wstring> findedElements = utility::getAvailableElements(projectsList->getValue(projectsList->getCurrentSelectionIndex()), current.getValue(current.getCurrentSelectionIndex()));

				for (const auto& i : findedElements)
				{
					elementsList->addValue(i);
				}
			});

		elementsList->setOnSelectionChange([projectsList, categoriesList, notesList](gui_framework::BaseComboBox& current)
			{
				if (current.getCurrentSelectionIndex() == -1)
				{
					return;
				}

				notesList->clear();
				vector<wstring> findedNotes = utility::getAvailableNotes
				(
					projectsList->getValue(projectsList->getCurrentSelectionIndex()),
					categoriesList->getValue(categoriesList->getCurrentSelectionIndex()),
					current.getValue(current.getCurrentSelectionIndex())
				);

				for (const auto& i : findedNotes)
				{
					notesList->addValue(i);
				}
			});

		result->show();

		return result;
	}

	EditNoteView::EditNoteView() :
		BaseView(make_unique<controllers::EditNoteController>(), EditNoteView::createEditNoteDialog(controller))
	{

	}

	void EditNoteView::update(const json::JSONParser& data)
	{
		using gui_framework::BaseDialogBox;

		string message = data.getString("message");

		if (data.getBool("success"))
		{
			if (BaseDialogBox::createMessageBox(utility::to_wstring(message, CP_UTF8), patch_notes_constants::successTitle, BaseDialogBox::messageBoxType::ok, static_cast<gui_framework::BaseComponent*>(window)) == BaseDialogBox::messageBoxResponse::ok)
			{
				Initializer::get().createUI();

				Initializer::get().closeEditNote();
			}
		}
		else
		{
			BaseDialogBox::createMessageBox(utility::to_wstring(message, CP_UTF8), patch_notes_constants::errorTitle, BaseDialogBox::messageBoxType::ok, static_cast<gui_framework::BaseComponent*>(window));
		}
	}
}
