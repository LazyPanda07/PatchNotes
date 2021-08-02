#include "CategoryConfigurationView.h"

#include "Composites/DialogBox.h"
#include "Components/EditControl.h"

#include "Initializer.h"
#include "Controllers/CategoryConfigurationController.h"
#include "Validation.h"
#include "PatchNotesUtility.h"
#include "PatchNotesConstants.h"

#include "Exceptions/ValidationException.h"

using namespace std;

CREATE_DEFAULT_WINDOW_FUNCTION(categoryConfiguration)

namespace views
{
	gui_framework::BaseComposite* CategoryConfigurationView::createCategoryDialog(const unique_ptr<controllers::BaseController>& controller, const wstring& projectNameAndVersion)
	{
		using gui_framework::DialogBox;
		using gui_framework::BaseDialogBox;

		validation::emptyValidation(projectNameAndVersion, L"Текущий проект");

		auto [x, y] = utility::getScreenCenter(gui_framework::standard_sizes::dialogBoxBuilderMinWidth, gui_framework::standard_sizes::dialogBoxBuilderMinHeight);

		DialogBox::DialogBoxBuilder builder(L"CategoryConfiguration", L"Конфигурация категории", x, y, "categoryConfiguration");

		gui_framework::utility::AdditionalCreationData<gui_framework::StaticControl> project(projectNameAndVersion);
		gui_framework::utility::AdditionalCreationData<gui_framework::EditControl> name(L"Название категории");
		gui_framework::utility::AdditionalCreationData<gui_framework::Button> add(L"Добавить", []() {});

		builder.
			addComponent<gui_framework::StaticControl>(L"ProjectCategory", 200, 20, DialogBox::DialogBoxBuilder::alignment::center, project).
			addComponent<gui_framework::EditControl>(L"CategoryName", 200, 20, DialogBox::DialogBoxBuilder::alignment::center, name).
			addComponent<gui_framework::Button>(L"AddCategory", 150, 40, DialogBox::DialogBoxBuilder::alignment::center, add, 0, 5);

		DialogBox* dialogBox = builder.build();

		dynamic_cast<gui_framework::Button*>(dialogBox->findChild(L"AddCategory"))->setOnClick([dialogBox, &controller]()
			{
				try
				{
					controller->receiveData(dialogBox);
				}
				catch (const exceptions::ValidationException& e)
				{
					BaseDialogBox::createMessageBox(e.getMessage(), errorTitle, BaseDialogBox::messageBoxType::ok, dialogBox);
				}
			});

		dynamic_cast<gui_framework::StaticControl*>(dialogBox->findChild(L"ProjectCategory"))->getHandle();

		dialogBox->show();

		return dialogBox;
	}

	CategoryConfigurationView::CategoryConfigurationView(const wstring& projectNameAndVersion) :
		BaseView(make_unique<controllers::CategoryConfigurationController>(), CategoryConfigurationView::createCategoryDialog(controller, projectNameAndVersion))
	{
		
	}

	void CategoryConfigurationView::update(const json::JSONParser& data)
	{
		using gui_framework::BaseDialogBox;

		bool success = data.get<bool>("success");
		string message = data.get<string>("message");

		if (success)
		{
			if (BaseDialogBox::createMessageBox(utility::to_wstring(message, CP_UTF8), successTitle, BaseDialogBox::messageBoxType::ok, dynamic_cast<gui_framework::BaseComponent*>(window)) == BaseDialogBox::messageBoxResponse::ok)
			{
				Initializer::get().createUI();

				Initializer::get().closeCategoryConfiguration();
			}
		}
		else
		{
			BaseDialogBox::createMessageBox(utility::to_wstring(message, CP_UTF8), errorTitle, BaseDialogBox::messageBoxType::ok, dynamic_cast<gui_framework::BaseComponent*>(window));
		}
	}
}
