#include "CategoryView.h"

#include "Composites/DialogBox.h"
#include "Components/EditControl.h"

#include "Initializer.h"
#include "Controllers/CategoryController.h"
#include "Validation.h"
#include "PatchNotesUtility.h"
#include "PatchNotesConstants.h"

#include "Exceptions/ValidationException.h"

using namespace std;

CREATE_DEFAULT_WINDOW_FUNCTION(categoryConfiguration)

namespace views
{
	gui_framework::BaseComposite* CategoryView::createCategoryDialog(const unique_ptr<controllers::BaseController>& controller, const wstring& projectNameAndVersion)
	{
		using gui_framework::DialogBox;
		using gui_framework::BaseDialogBox;

		localization::WTextLocalization& textLocalization = localization::WTextLocalization::get();

		validation::emptyValidation(projectNameAndVersion, textLocalization[patch_notes_localization::currentProject]);

		auto [x, y] = utility::getScreenCenter(gui_framework::standard_sizes::dialogBoxBuilderMinWidth, gui_framework::standard_sizes::dialogBoxBuilderMinHeight);

		DialogBox::DialogBoxBuilder builder(L"CategoryConfiguration", textLocalization[patch_notes_localization::categoryConfiguration], x, y, "categoryConfiguration");

		gui_framework::utility::AdditionalCreationData<gui_framework::StaticControl> project(projectNameAndVersion);
		gui_framework::utility::AdditionalCreationData<gui_framework::EditControl> name(textLocalization[patch_notes_localization::categoryName]);
		gui_framework::utility::AdditionalCreationData<gui_framework::Button> add(textLocalization[patch_notes_localization::add], []() {});

		builder.
			addComponent<gui_framework::StaticControl>(L"ProjectCategory", 200, 20, DialogBox::DialogBoxBuilder::alignment::center, project).
			addComponent<gui_framework::EditControl>(L"CategoryName", 200, 20, DialogBox::DialogBoxBuilder::alignment::center, name).
			addComponent<gui_framework::Button>(L"AddCategory", 150, 40, DialogBox::DialogBoxBuilder::alignment::center, add, 0, 5);

		DialogBox* dialogBox = builder.build();

		static_cast<gui_framework::Button*>(dialogBox->findChild(L"AddCategory"))->setOnClick([dialogBox, &controller]()
			{
				try
				{
					controller->receiveData(dialogBox);
				}
				catch (const exceptions::ValidationException& e)
				{
					BaseDialogBox::createMessageBox(e.getMessage(), patch_notes_constants::errorTitle, BaseDialogBox::messageBoxType::ok, dialogBox);
				}
			});

		static_cast<gui_framework::StaticControl*>(dialogBox->findChild(L"ProjectCategory"))->getHandle();

		dialogBox->show();

		return dialogBox;
	}

	CategoryView::CategoryView(const wstring& projectNameAndVersion) :
		BaseView(make_unique<controllers::CategoryController>(), CategoryView::createCategoryDialog(controller, projectNameAndVersion))
	{
		
	}

	void CategoryView::update(const json::JSONParser& data)
	{
		using gui_framework::BaseDialogBox;

		bool success = data.getBool("success");
		string message = data.getString("message");

		if (success)
		{
			if (BaseDialogBox::createMessageBox(utility::to_wstring(message, CP_UTF8), patch_notes_constants::successTitle, BaseDialogBox::messageBoxType::ok, static_cast<gui_framework::BaseComponent*>(window)) == BaseDialogBox::messageBoxResponse::ok)
			{
				Initializer::get().createUI();

				Initializer::get().closeCategory();
			}
		}
		else
		{
			BaseDialogBox::createMessageBox(utility::to_wstring(message, CP_UTF8), patch_notes_constants::errorTitle, BaseDialogBox::messageBoxType::ok, static_cast<gui_framework::BaseComponent*>(window));
		}
	}
}
