#include "EditNoteView.h"

#include "Composites/DialogBox.h"

#include "Controllers/Editing/EditNoteController.h"
#include "PatchNotesUtility.h"

using namespace std;

CREATE_DEFAULT_WINDOW_FUNCTION(editNote)

namespace views
{
	gui_framework::BaseComposite* EditNoteView::createEditNoteDialog(const std::unique_ptr<controllers::BaseController>& controller)
	{
		using gui_framework::DialogBox;

		auto [x, y] = utility::getScreenCenter(gui_framework::standard_sizes::dialogBoxBuilderMinWidth, gui_framework::standard_sizes::dialogBoxBuilderMinHeight);

		DialogBox::DialogBoxBuilder builder(L"EditNote", L"Редактирование конфигурации", x, y, "editNote");

		gui_framework::utility::AdditionalCreationData<gui_framework::DropDownListComboBox> configurationToEdit(utility::getAvailableProjectsFiles());
		gui_framework::utility::AdditionalCreationData<gui_framework::EditControl> newNoteName(L"Новое название конфигурации(это поле может быть пустым)");
		gui_framework::utility::AdditionalCreationData<gui_framework::EditControl> newNoteVersion(L"Новая версия конфигурации(это поле может быть пустым)");
		gui_framework::utility::AdditionalCreationData<gui_framework::Button> confirm(L"Изменить", []() {});

		builder.
			addComponent<gui_framework::DropDownListComboBox>(L"ProjectsToEdit", 200, 25, DialogBox::DialogBoxBuilder::alignment::center, configurationToEdit).
			addComponent<gui_framework::EditControl>(L"NewNoteName", 200, 25, DialogBox::DialogBoxBuilder::alignment::center, newNoteName).
			addComponent<gui_framework::EditControl>(L"NewNoteVersion", 200, 25, DialogBox::DialogBoxBuilder::alignment::center, newNoteVersion).
			addComponent<gui_framework::Button>(L"ConfirmEditNote", 200, 20, DialogBox::DialogBoxBuilder::alignment::center, confirm);

		DialogBox* result = builder.build();

		static_cast<gui_framework::Button*>(result->findChild(L"ConfirmEditNote"))->setOnClick([&controller, result]()
			{
				if (static_cast<gui_framework::DropDownListComboBox*>(result->findChild(L"ProjectsToEdit"))->getCurrentSelectionIndex() == -1)
				{
					return;
				}

				controller->receiveData(result);
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

	}
}
