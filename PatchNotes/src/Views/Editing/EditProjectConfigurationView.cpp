#include "EditProjectConfigurationView.h"

#include "Composites/DialogBox.h"

#include "Controllers/Editing/EditProjectConfigurationController.h"
#include "PatchNotesUtility.h"

using namespace std;

CREATE_DEFAULT_WINDOW_FUNCTION(editConfiguration)

namespace views
{
	gui_framework::BaseComposite* EditProjectConfigurationView::createEditProjectConfigurationDialog(const std::unique_ptr<controllers::BaseController>& controller)
	{
		using gui_framework::DialogBox;

		auto [x, y] = utility::getScreenCenter(gui_framework::standard_sizes::dialogBoxBuilderMinWidth, gui_framework::standard_sizes::dialogBoxBuilderMinHeight);

		DialogBox::DialogBoxBuilder builder(L"EditConfiguration", L"Редактирование конфигурации", x, y, "editConfiguration");

		gui_framework::utility::AdditionalCreationData<gui_framework::DropDownListComboBox> configurationToEdit(utility::getAvailableProjectsFiles());
		gui_framework::utility::AdditionalCreationData<gui_framework::EditControl> newConfigurationName(L"Новое название конфигурации");
		gui_framework::utility::AdditionalCreationData<gui_framework::EditControl> newConfigurationVersion(L"Новая версия конфигурации");
		gui_framework::utility::AdditionalCreationData<gui_framework::Button> confirm(L"Изменить", []() {});

		builder.
			addComponent<gui_framework::DropDownListComboBox>(L"ProjectsToEdit", 300, 25, DialogBox::DialogBoxBuilder::alignment::center, configurationToEdit).
			addComponent<gui_framework::EditControl>(L"NewConfigurationName", 300, 25, DialogBox::DialogBoxBuilder::alignment::center, newConfigurationName).
			addComponent<gui_framework::EditControl>(L"NewConfigurationVersion", 300, 25, DialogBox::DialogBoxBuilder::alignment::center, newConfigurationVersion).
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

	}
}
