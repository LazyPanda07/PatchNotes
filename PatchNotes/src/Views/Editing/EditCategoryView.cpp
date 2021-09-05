#include "EditCategoryView.h"

#include "Composites/DialogBox.h"

#include "Controllers/Editing/EditCategoryController.h"
#include "PatchNotesUtility.h"

using namespace std;

CREATE_DEFAULT_WINDOW_FUNCTION(editCategory)

namespace views
{
	gui_framework::BaseComposite* EditCategoryView::createEditCategoryDialog(const std::unique_ptr<controllers::BaseController>& controller)
	{
		using gui_framework::DialogBox;

		auto [x, y] = utility::getScreenCenter(gui_framework::standard_sizes::dialogBoxBuilderMinWidth, gui_framework::standard_sizes::dialogBoxBuilderMinHeight);

		DialogBox::DialogBoxBuilder builder(L"EditCategory", L"Редактирование конфигурации", x, y, "editCategory");

		gui_framework::utility::AdditionalCreationData<gui_framework::DropDownListComboBox> configurationToEdit(utility::getAvailableProjectsFiles());
		gui_framework::utility::AdditionalCreationData<gui_framework::EditControl> newCategoryName(L"Новое название конфигурации(это поле может быть пустым)");
		gui_framework::utility::AdditionalCreationData<gui_framework::EditControl> newCategoryVersion(L"Новая версия конфигурации(это поле может быть пустым)");
		gui_framework::utility::AdditionalCreationData<gui_framework::Button> confirm(L"Изменить", []() {});

		builder.
			addComponent<gui_framework::DropDownListComboBox>(L"ProjectsToEdit", 200, 25, DialogBox::DialogBoxBuilder::alignment::center, configurationToEdit).
			addComponent<gui_framework::EditControl>(L"NewCategoryName", 200, 25, DialogBox::DialogBoxBuilder::alignment::center, newCategoryName).
			addComponent<gui_framework::EditControl>(L"NewCategoryVersion", 200, 25, DialogBox::DialogBoxBuilder::alignment::center, newCategoryVersion).
			addComponent<gui_framework::Button>(L"ConfirmEditCategory", 200, 20, DialogBox::DialogBoxBuilder::alignment::center, confirm);

		DialogBox* result = builder.build();

		static_cast<gui_framework::Button*>(result->findChild(L"ConfirmEditCategory"))->setOnClick([&controller, result]()
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

	EditCategoryView::EditCategoryView() :
		BaseView(make_unique<controllers::EditCategoryController>(), EditCategoryView::createEditCategoryDialog(controller))
	{

	}

	void EditCategoryView::update(const json::JSONParser& data)
	{

	}
}
