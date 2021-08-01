#include "CategoryConfigurationView.h"

#include "Composites/DialogBox.h"
#include "Components/EditControl.h"

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

	CategoryConfigurationView::CategoryConfigurationView(const wstring& projectNameAndVersion, unique_ptr<controllers::BaseController>& patchNotesController) :
		BaseView(make_unique<controllers::CategoryConfigurationController>(), CategoryConfigurationView::createCategoryDialog(controller, projectNameAndVersion), true),
		patchNotesController(patchNotesController)
	{
		
	}

	void CategoryConfigurationView::update(const json::JSONParser& data)
	{
		patchNotesController->getModel()->getObservers().back()->update(data);
	}
}
