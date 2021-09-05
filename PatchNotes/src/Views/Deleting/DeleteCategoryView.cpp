#include "DeleteCategoryView.h"

#include "Composites/DialogBox.h"

#include "Controllers/Deleting/DeleteCategoryController.h"
#include "PatchNotesUtility.h"
#include "PatchNotesConstants.h"
#include "Initializer.h"

using namespace std;

CREATE_DEFAULT_WINDOW_FUNCTION(deleteCategory)

namespace views
{
	gui_framework::BaseComposite* DeleteCategoryView::createDeleteCategoryDialog(const unique_ptr<controllers::BaseController>& controller)
	{
		using gui_framework::DialogBox;

		auto [x, y] = utility::getScreenCenter(gui_framework::standard_sizes::dialogBoxBuilderMinWidth, gui_framework::standard_sizes::dialogBoxBuilderMinHeight);

		DialogBox::DialogBoxBuilder builder(L"DeleteCategory", L"Удаление категории", x, y, "deleteCategory");

		gui_framework::utility::AdditionalCreationData<gui_framework::DropDownListComboBox> availableProjects(utility::getAvailableProjectsFiles());
		gui_framework::utility::AdditionalCreationData<gui_framework::Button> confirm(L"Удалить", []() {});

		builder.
			addComponent<gui_framework::DropDownListComboBox>(L"AvailableProjects", 200, 25, DialogBox::DialogBoxBuilder::alignment::center, availableProjects).
			addComponent<gui_framework::DropDownListComboBox>(L"CategoryToDelete", 200, 25, DialogBox::DialogBoxBuilder::alignment::center).
			addComponent<gui_framework::Button>(L"ConfirmDeleteCategory", 200, 20, DialogBox::DialogBoxBuilder::alignment::center, confirm);

		DialogBox* result = builder.build();
		gui_framework::DropDownListComboBox* categories = static_cast<gui_framework::DropDownListComboBox*>(result->findChild(L"CategoryToDelete"));

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

		static_cast<gui_framework::Button*>(result->findChild(L"ConfirmDeleteCategory"))->setOnClick([&controller, result]()
			{
				if (static_cast<gui_framework::DropDownListComboBox*>(result->findChild(L"AvailableProjects"))->getCurrentSelectionIndex() == -1)
				{
					return;
				}

				if (static_cast<gui_framework::DropDownListComboBox*>(result->findChild(L"CategoryToDelete"))->getCurrentSelectionIndex() == -1)
				{
					return;
				}

				controller->receiveData(result);
			});

		result->show();

		return result;
	}

	DeleteCategoryView::DeleteCategoryView() :
		BaseView(make_unique<controllers::DeleteCategoryController>(), DeleteCategoryView::createDeleteCategoryDialog(controller))
	{

	}

	void DeleteCategoryView::update(const json::JSONParser& data)
	{
		using gui_framework::BaseDialogBox;

		bool success = data.getBool("success");
		string message = data.getString("message");
		const wstring& title = success ? patch_notes_constants::successTitle : patch_notes_constants::errorTitle;

		if (BaseDialogBox::createMessageBox(utility::to_wstring(message, CP_UTF8), title, BaseDialogBox::messageBoxType::ok, static_cast<gui_framework::BaseComponent*>(window)) == BaseDialogBox::messageBoxResponse::ok)
		{
			Initializer::get().createUI();

			Initializer::get().closeDeleteCategory();
		}
	}
}
