#include "EditElementView.h"

#include "Composites/DialogBox.h"

#include "Controllers/Editing/EditElementController.h"
#include "PatchNotesUtility.h"
#include "PatchNotesConstants.h"
#include "Initializer.h"

using namespace std;

CREATE_DEFAULT_WINDOW_FUNCTION(editElement)

namespace views
{
	gui_framework::BaseComposite* EditElementView::createEditElementDialog(const std::unique_ptr<controllers::BaseController>& controller)
	{
		using gui_framework::DialogBox;

		auto [x, y] = utility::getScreenCenter(gui_framework::standard_sizes::dialogBoxBuilderMinWidth, gui_framework::standard_sizes::dialogBoxBuilderMinHeight);

		DialogBox::DialogBoxBuilder builder(L"EditElement", L"Редактирование элемента", x, y, "editElement");

		gui_framework::utility::AdditionalCreationData<gui_framework::DropDownListComboBox> projects(utility::getAvailableProjectsFiles());
		gui_framework::utility::AdditionalCreationData<gui_framework::EditControl> newElementName(L"Новое название элемента");
		gui_framework::utility::AdditionalCreationData<gui_framework::Button> confirm(L"Изменить", []() {});

		builder.
			addComponent<gui_framework::DropDownListComboBox>(L"Projects", 200, 25, DialogBox::DialogBoxBuilder::alignment::center, projects).
			addComponent<gui_framework::DropDownListComboBox>(L"Categories", 200, 25, DialogBox::DialogBoxBuilder::alignment::center).
			addComponent<gui_framework::DropDownListComboBox>(L"Elements", 200, 25, DialogBox::DialogBoxBuilder::alignment::center).
			addComponent<gui_framework::EditControl>(L"NewElementName", 200, 20, DialogBox::DialogBoxBuilder::alignment::center, newElementName).
			addComponent<gui_framework::Button>(L"ConfirmEditElement", 200, 20, DialogBox::DialogBoxBuilder::alignment::center, confirm);

		DialogBox* result = builder.build();
		gui_framework::DropDownListComboBox* projectsList = static_cast<gui_framework::DropDownListComboBox*>(result->findChild(L"Projects"));
		gui_framework::DropDownListComboBox* categories = static_cast<gui_framework::DropDownListComboBox*>(result->findChild(L"Categories"));
		gui_framework::DropDownListComboBox* elements = static_cast<gui_framework::DropDownListComboBox*>(result->findChild(L"Elements"));

		static_cast<gui_framework::Button*>(result->findChild(L"ConfirmEditElement"))->setOnClick([&controller, result]()
			{
				if (static_cast<gui_framework::DropDownListComboBox*>(result->findChild(L"Projects"))->getCurrentSelectionIndex() == -1)
				{
					return;
				}
				else if (static_cast<gui_framework::EditControl*>(result->findChild(L"NewElementName"))->getText().empty())
				{
					return;
				}

				controller->receiveData(result);
			});

		projectsList->setOnSelectionChange([categories](gui_framework::BaseComboBox& current)
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

		categories->setOnSelectionChange([projectsList, elements](gui_framework::BaseComboBox& current)
			{
				if (current.getCurrentSelectionIndex() == -1)
				{
					return;
				}

				elements->clear();
				vector<wstring> findedElements = utility::getAvailableElements(projectsList->getValue(projectsList->getCurrentSelectionIndex()), current.getValue(current.getCurrentSelectionIndex()));

				for (const auto& i : findedElements)
				{
					elements->addValue(i);
				}
			});

		result->show();

		return result;
	}

	EditElementView::EditElementView() :
		BaseView(make_unique<controllers::EditElementController>(), EditElementView::createEditElementDialog(controller))
	{

	}

	void EditElementView::update(const json::JSONParser& data)
	{
		using gui_framework::BaseDialogBox;

		string message = data.getString("message");

		if (data.getBool("success"))
		{
			if (BaseDialogBox::createMessageBox(utility::to_wstring(message, CP_UTF8), patch_notes_constants::successTitle, BaseDialogBox::messageBoxType::ok, static_cast<gui_framework::BaseComponent*>(window)) == BaseDialogBox::messageBoxResponse::ok)
			{
				Initializer::get().createUI();

				Initializer::get().closeEditElement();
			}
		}
		else
		{
			BaseDialogBox::createMessageBox(utility::to_wstring(message, CP_UTF8), patch_notes_constants::errorTitle, BaseDialogBox::messageBoxType::ok, static_cast<gui_framework::BaseComponent*>(window));
		}
	}
}
