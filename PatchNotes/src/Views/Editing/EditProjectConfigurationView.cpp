#include "EditProjectConfigurationView.h"

#include "Composites/DialogBox.h"

#include "Controllers/Editing/EditProjectConfigurationController.h"
#include "Initializer.h"
#include "PatchNotesUtility.h"
#include "PatchNotesConstants.h"

using namespace std;

CREATE_DEFAULT_WINDOW_FUNCTION(editConfiguration)

namespace views
{
	gui_framework::BaseComposite* EditProjectConfigurationView::createEditProjectConfigurationDialog(const std::unique_ptr<controllers::BaseController>& controller)
	{
		using gui_framework::DialogBox;

		auto [x, y] = utility::getScreenCenter(gui_framework::standard_sizes::dialogBoxBuilderMinWidth, gui_framework::standard_sizes::dialogBoxBuilderMinHeight);
		localization::WTextLocalization& textLocalization = localization::WTextLocalization::get();

		DialogBox::DialogBoxBuilder builder(L"EditConfiguration", textLocalization[patch_notes_localization::editConfiguration], x, y, "editConfiguration");

		gui_framework::utility::AdditionalCreationData<gui_framework::DropDownListComboBox> configurationToEdit(utility::getAvailableProjectsFiles());
		gui_framework::utility::AdditionalCreationData<gui_framework::EditControl> newConfigurationName(textLocalization[patch_notes_localization::newConfigurationName]);
		gui_framework::utility::AdditionalCreationData<gui_framework::EditControl> newConfigurationVersion(textLocalization[patch_notes_localization::newVersion]);
		gui_framework::utility::AdditionalCreationData<gui_framework::Button> confirm(textLocalization[patch_notes_localization::editButton], []() {});

		builder.
			addComponent<gui_framework::DropDownListComboBox>(L"ProjectsToEdit", 300, 25, DialogBox::DialogBoxBuilder::alignment::center, configurationToEdit).
			addComponent<gui_framework::EditControl>(L"NewConfigurationName", 300, 20, DialogBox::DialogBoxBuilder::alignment::center, newConfigurationName).
			addComponent<gui_framework::EditControl>(L"NewConfigurationVersion", 300, 20, DialogBox::DialogBoxBuilder::alignment::center, newConfigurationVersion).
			addComponent<gui_framework::Button>(L"ConfirmEditConfiguration", 300, 20, DialogBox::DialogBoxBuilder::alignment::center, confirm);

		DialogBox* result = builder.build();

		static_cast<gui_framework::Button*>(result->findChild(L"ConfirmEditConfiguration"))->setOnClick([&controller, result]()
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

	EditProjectConfigurationView::EditProjectConfigurationView() :
		BaseView(make_unique<controllers::EditProjectConfigurationController>(), EditProjectConfigurationView::createEditProjectConfigurationDialog(controller))
	{

	}

	void EditProjectConfigurationView::update(const json::JSONParser& data)
	{
		using gui_framework::BaseDialogBox;

		string message = data.getString("message");

		if (data.getBool("success"))
		{
			if (BaseDialogBox::createMessageBox(utility::to_wstring(message, CP_UTF8), patch_notes_constants::successTitle, BaseDialogBox::messageBoxType::ok, static_cast<gui_framework::BaseComponent*>(window)) == BaseDialogBox::messageBoxResponse::ok)
			{
				Initializer::get().createUI();

				Initializer::get().closeEditProjectConfiguration();
			}
		}
		else
		{
			BaseDialogBox::createMessageBox(utility::to_wstring(message, CP_UTF8), patch_notes_constants::errorTitle, BaseDialogBox::messageBoxType::ok, static_cast<gui_framework::BaseComponent*>(window));
		}
	}
}
