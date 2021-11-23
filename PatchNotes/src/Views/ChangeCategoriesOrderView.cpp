#include "ChangeCategoriesOrderView.h"

#include "Composites/DialogBox.h"

#include "Controllers/ChangeCategoriesOrderController.h"
#include "PatchNotesUtility.h"
#include "Initializer.h"
#include "PatchNotesConstants.h"

using namespace std;

CREATE_DEFAULT_WINDOW_FUNCTION(changeCategoriesOrder)

namespace views
{
	gui_framework::BaseComposite* ChangeCategoriesOrderView::createChangeCategoriesOrderDialog(const std::unique_ptr<controllers::BaseController>& controller, const std::wstring& projectConfiguration)
	{
		using gui_framework::DialogBox;

		auto [x, y] = utility::getScreenCenter(gui_framework::standard_sizes::dialogBoxBuilderMinWidth, gui_framework::standard_sizes::dialogBoxBuilderMinHeight);
		localization::WTextLocalization& textLocalization = localization::WTextLocalization::get();

		DialogBox::DialogBoxBuilder builder(L"ChangeCategoriesOrder", textLocalization[patch_notes_localization::changeCategoriesOrder], x, y, "changeCategoriesOrder");

		vector<wstring> categories(utility::getAvailableCategories(projectConfiguration));
		gui_framework::utility::AdditionalCreationData<gui_framework::StaticControl> currentProject(projectConfiguration);
		gui_framework::utility::AdditionalCreationData<gui_framework::Button> confirm(textLocalization[patch_notes_localization::editButton], []() {});
		wstring categoriesOrder;

		builder.
			addComponent<gui_framework::StaticControl>(L"ProjectConfiguration", 300, 20, gui_framework::DialogBox::DialogBoxBuilder::alignment::center, currentProject).
			addComponent<gui_framework::RichEdit>(L"Categories", 300, 300, gui_framework::DialogBox::DialogBoxBuilder::alignment::center).
			addComponent<gui_framework::Button>(L"ConfirmCategoriesOrder", 300, 20, DialogBox::DialogBoxBuilder::alignment::center, confirm);

		DialogBox* result = builder.build();

		static_cast<gui_framework::Button*>(result->findChild(L"ConfirmCategoriesOrder"))->setOnClick([&controller, result]()
			{
				controller->receiveData(result);
			});

		for (const auto& i : categories)
		{
			categoriesOrder += i + L'\r';
		}

		static_cast<gui_framework::RichEdit*>(result->findChild(L"Categories"))->setText(categoriesOrder);

		result->show();

		return result;
	}

	ChangeCategoriesOrderView::ChangeCategoriesOrderView(const wstring& projectConfiguration) :
		BaseView(make_unique<controllers::ChangeCategoriesOrderController>(), ChangeCategoriesOrderView::createChangeCategoriesOrderDialog(controller, projectConfiguration))
	{

	}

	void ChangeCategoriesOrderView::update(const json::JSONParser& data)
	{
		using gui_framework::BaseDialogBox;

		string message = data.getString("message");

		if (data.getBool("success"))
		{
			if (BaseDialogBox::createMessageBox(utility::to_wstring(message, CP_UTF8), patch_notes_constants::successTitle, BaseDialogBox::messageBoxType::ok, static_cast<gui_framework::BaseComponent*>(window)) == BaseDialogBox::messageBoxResponse::ok)
			{
				Initializer::get().createUI();

				Initializer::get().closeChangeCategoriesOrder();
			}
		}
		else
		{
			BaseDialogBox::createMessageBox(utility::to_wstring(message, CP_UTF8), patch_notes_constants::errorTitle, BaseDialogBox::messageBoxType::ok, static_cast<gui_framework::BaseComponent*>(window));
		}
	}
}
