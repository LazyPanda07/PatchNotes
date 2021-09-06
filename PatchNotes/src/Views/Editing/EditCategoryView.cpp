#include "EditCategoryView.h"

#include "Composites/DialogBox.h"

#include "Controllers/Editing/EditCategoryController.h"
#include "PatchNotesUtility.h"
#include "PatchNotesConstants.h"
#include "Initializer.h"

using namespace std;

CREATE_DEFAULT_WINDOW_FUNCTION(editCategory)

namespace views
{
	gui_framework::BaseComposite* EditCategoryView::createEditCategoryDialog(const std::unique_ptr<controllers::BaseController>& controller)
	{
		using gui_framework::DialogBox;

		auto [x, y] = utility::getScreenCenter(gui_framework::standard_sizes::dialogBoxBuilderMinWidth, gui_framework::standard_sizes::dialogBoxBuilderMinHeight);

		DialogBox::DialogBoxBuilder builder(L"EditCategory", L"Редактирование категории", x, y, "editCategory");

		gui_framework::utility::AdditionalCreationData<gui_framework::DropDownListComboBox> projects(utility::getAvailableProjectsFiles());
		gui_framework::utility::AdditionalCreationData<gui_framework::EditControl> newCategoryName(L"Новое название категории");
		gui_framework::utility::AdditionalCreationData<gui_framework::Button> confirm(L"Изменить", []() {});

		builder.
			addComponent<gui_framework::DropDownListComboBox>(L"Projects", 200, 25, DialogBox::DialogBoxBuilder::alignment::center, projects).
			addComponent<gui_framework::DropDownListComboBox>(L"Categories", 200, 25, DialogBox::DialogBoxBuilder::alignment::center).
			addComponent<gui_framework::EditControl>(L"NewCategoryName", 200, 20, DialogBox::DialogBoxBuilder::alignment::center, newCategoryName).
			addComponent<gui_framework::Button>(L"ConfirmEditCategory", 200, 20, DialogBox::DialogBoxBuilder::alignment::center, confirm);

		DialogBox* result = builder.build();
		gui_framework::DropDownListComboBox* categories = static_cast<gui_framework::DropDownListComboBox*>(result->findChild(L"Categories"));

		static_cast<gui_framework::Button*>(result->findChild(L"ConfirmEditCategory"))->setOnClick([&controller, result]()
			{
				if (static_cast<gui_framework::DropDownListComboBox*>(result->findChild(L"Projects"))->getCurrentSelectionIndex() == -1)
				{
					return;
				}

				controller->receiveData(result);
			});

		static_cast<gui_framework::DropDownComboBox*>(result->findChild(L"Projects"))->setOnSelectionChange([categories](gui_framework::BaseComboBox& current)
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

		result->show();

		return result;
	}

	EditCategoryView::EditCategoryView() :
		BaseView(make_unique<controllers::EditCategoryController>(), EditCategoryView::createEditCategoryDialog(controller))
	{

	}

	void EditCategoryView::update(const json::JSONParser& data)
	{
		using gui_framework::BaseDialogBox;

		string message = data.getString("message");

		if (data.getBool("success"))
		{
			if (BaseDialogBox::createMessageBox(utility::to_wstring(message, CP_UTF8), patch_notes_constants::successTitle, BaseDialogBox::messageBoxType::ok, static_cast<gui_framework::BaseComponent*>(window)) == BaseDialogBox::messageBoxResponse::ok)
			{
				Initializer::get().createUI();

				Initializer::get().closeEditCategory();
			}
		}
		else
		{
			BaseDialogBox::createMessageBox(utility::to_wstring(message, CP_UTF8), patch_notes_constants::errorTitle, BaseDialogBox::messageBoxType::ok, static_cast<gui_framework::BaseComponent*>(window));
		}
	}
}
