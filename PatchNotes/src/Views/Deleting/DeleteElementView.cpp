#include "DeleteElementView.h"

#include "ComponentsHeader.h"
#include "CompositesHeader.h"
#include "Utility/AdditionalCreationData/ComboBoxAdditionalCreationData.h"
#include "Utility/AdditionalCreationData/ButtonAdditionalCreationData.h"

#include "Controllers/Deleting/DeleteElementController.h"
#include "PatchNotesUtility.h"
#include "PatchNotesConstants.h"
#include "Initializer.h"

using namespace std;

CREATE_DEFAULT_WINDOW_FUNCTION(deleteElement)

namespace views
{
	gui_framework::BaseComposite* DeleteElementView::createDeleteElementDialog(const unique_ptr<controllers::BaseController>& controller)
	{
		using gui_framework::DialogBox;

		auto [x, y] = utility::getScreenCenter(gui_framework::standard_sizes::dialogBoxBuilderMinWidth, gui_framework::standard_sizes::dialogBoxBuilderMinHeight);

		DialogBox::DialogBoxBuilder builder(L"DeleteElement", localization::WTextLocalization::get()[patch_notes_localization::deleteElement], x, y, "deleteElement");

		gui_framework::utility::AdditionalCreationData<gui_framework::DropDownListComboBox> availableProjects(utility::getAvailableProjectsFiles());
		gui_framework::utility::AdditionalCreationData<gui_framework::Button> confirm(localization::WTextLocalization::get()[patch_notes_localization::deleteButton], []() {});

		builder.
			addComponent<gui_framework::DropDownListComboBox>(L"AvailableProjects", 200, 25, DialogBox::DialogBoxBuilder::alignment::center, availableProjects).
			addComponent<gui_framework::DropDownListComboBox>(L"AvailableCategories", 200, 25, DialogBox::DialogBoxBuilder::alignment::center).
			addComponent<gui_framework::DropDownListComboBox>(L"ElementToDelete", 200, 25, DialogBox::DialogBoxBuilder::alignment::center).
			addComponent<gui_framework::Button>(L"ConfirmDeleteElement", 200, 20, DialogBox::DialogBoxBuilder::alignment::center, confirm);

		DialogBox* result = builder.build();
		gui_framework::DropDownListComboBox* categories = static_cast<gui_framework::DropDownListComboBox*>(result->findChild(L"AvailableCategories"));
		gui_framework::DropDownListComboBox* elements = static_cast<gui_framework::DropDownListComboBox*>(result->findChild(L"ElementToDelete"));

		static_cast<gui_framework::DropDownListComboBox*>(result->findChild(L"AvailableProjects"))->setOnSelectionChange([categories, elements](gui_framework::BaseComboBox& current)
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

		static_cast<gui_framework::Button*>(result->findChild(L"ConfirmDeleteElement"))->setOnClick([&controller, result]()
			{
				if (static_cast<gui_framework::DropDownListComboBox*>(result->findChild(L"AvailableProjects"))->getCurrentSelectionIndex() == -1)
				{
					return;
				}

				if (static_cast<gui_framework::DropDownListComboBox*>(result->findChild(L"AvailableCategories"))->getCurrentSelectionIndex() == -1)
				{
					return;
				}

				if (static_cast<gui_framework::DropDownListComboBox*>(result->findChild(L"ElementToDelete"))->getCurrentSelectionIndex() == -1)
				{
					return;
				}

				controller->receiveData(result);
			});

		result->show();

		return result;
	}

	DeleteElementView::DeleteElementView() :
		BaseView(make_unique<controllers::DeleteElementController>(), DeleteElementView::createDeleteElementDialog(controller))
	{

	}

	void DeleteElementView::update(const json::JSONParser& data)
	{
		using gui_framework::BaseDialogBox;

		bool success = data.getBool("success");
		string message = data.getString("message");
		const wstring& title = success ? patch_notes_constants::successTitle : patch_notes_constants::errorTitle;

		if (BaseDialogBox::createMessageBox(utility::to_wstring(message, CP_UTF8), title, BaseDialogBox::messageBoxType::ok, static_cast<gui_framework::BaseComponent*>(window)) == BaseDialogBox::messageBoxResponse::ok)
		{
			Initializer::get().createUI();

			Initializer::get().closeDeleteElement();
		}
	}
}
