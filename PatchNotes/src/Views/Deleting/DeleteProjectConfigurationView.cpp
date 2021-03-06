#include "DeleteProjectConfigurationView.h"

#include "ComponentsHeader.h"
#include "CompositesHeader.h"
#include "Utility/AdditionalCreationData/ComboBoxAdditionalCreationData.h"
#include "Utility/AdditionalCreationData/ButtonAdditionalCreationData.h"

#include "Controllers/Deleting/DeleteProjectConfigurationController.h"
#include "PatchNotesUtility.h"
#include "PatchNotesConstants.h"
#include "Initializer.h"

using namespace std;

CREATE_DEFAULT_WINDOW_FUNCTION(deleteConfiguration)

namespace views
{
	gui_framework::BaseComposite* DeleteProjectConfigurationView::createDeleteProjectConfigurationDialog(const unique_ptr<controllers::BaseController>& controller)
	{
		using gui_framework::DialogBox;

		auto [x, y] = utility::getScreenCenter(gui_framework::standard_sizes::dialogBoxBuilderMinWidth, gui_framework::standard_sizes::dialogBoxBuilderMinHeight);

		DialogBox::DialogBoxBuilder builder(L"DeleteConfiguration", localization::WTextLocalization::get()[patch_notes_localization::deleteConfiguration], x, y, "deleteConfiguration");

		gui_framework::utility::AdditionalCreationData<gui_framework::DropDownListComboBox> configurationToDelete(utility::getAvailableProjectsFiles());
		gui_framework::utility::AdditionalCreationData<gui_framework::Button> confirm(localization::WTextLocalization::get()[patch_notes_localization::deleteButton], []() {});

		builder.
			addComponent<gui_framework::DropDownListComboBox>(L"ProjectsToDelete", 200, 25, DialogBox::DialogBoxBuilder::alignment::center, configurationToDelete).
			addComponent<gui_framework::Button>(L"ConfirmDeleteConfiguration", 200, 20, DialogBox::DialogBoxBuilder::alignment::center, confirm);

		DialogBox* result = builder.build();

		static_cast<gui_framework::Button*>(result->findChild(L"ConfirmDeleteConfiguration"))->setOnClick([&controller, result]()
			{
				if (static_cast<gui_framework::DropDownListComboBox*>(result->findChild(L"ProjectsToDelete"))->getCurrentSelectionIndex() == -1)
				{
					return;
				}

				controller->receiveData(result);
			});

		result->show();

		return result;
	}

	DeleteProjectConfigurationView::DeleteProjectConfigurationView() :
		BaseView(make_unique<controllers::DeleteProjectConfigurationController>(), DeleteProjectConfigurationView::createDeleteProjectConfigurationDialog(controller))
	{

	}

	void DeleteProjectConfigurationView::update(const json::JSONParser& data)
	{
		using gui_framework::BaseDialogBox;

		bool success = data.getBool("success");
		string message = data.getString("message");
		const wstring& title = success ? patch_notes_constants::successTitle : patch_notes_constants::errorTitle;

		if (BaseDialogBox::createMessageBox(utility::to_wstring(message, CP_UTF8), title, BaseDialogBox::messageBoxType::ok, static_cast<gui_framework::BaseComponent*>(window)) == BaseDialogBox::messageBoxResponse::ok)
		{
			Initializer::get().createUI();

			Initializer::get().closeDeleteConfiguration();
		}
	}
}
