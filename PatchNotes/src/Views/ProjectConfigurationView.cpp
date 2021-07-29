#include "ProjectConfigurationView.h"

#include "Composites/DialogBox.h"
#include "Components/EditControl.h"

#include "PatchNotesUtility.h"

using namespace std;

CREATE_DEFAULT_WINDOW_FUNCTION(projectConfiguration)

namespace views
{
	gui_framework::BaseComposite* ProjectConfigurationView::createConfigurationDialog(const shared_ptr<controllers::BaseController>& controller)
	{
		using gui_framework::DialogBox;
		using gui_framework::BaseDialogBox;

		auto [x, y] = utility::getScreenCenter(gui_framework::standard_sizes::dialogBoxBuilderMinWidth, gui_framework::standard_sizes::dialogBoxBuilderMinHeight);

		DialogBox::DialogBoxBuilder builder(L"ProjectConfiguration", L"Конфигурация проекта", x, y, "projectConfiguration");

		gui_framework::utility::AdditionalCreationData<gui_framework::EditControl> name(L"Название проекта");
		gui_framework::utility::AdditionalCreationData<gui_framework::EditControl> version(L"Версия проекта");
		gui_framework::utility::AdditionalCreationData<gui_framework::Button> add(L"Добавить", []() {});

		builder.
			addComponent<gui_framework::EditControl>(L"ProjectName", 200, 20, DialogBox::DialogBoxBuilder::alignment::center, name).
			addComponent<gui_framework::EditControl>(L"ProjectVersion", 200, 20, DialogBox::DialogBoxBuilder::alignment::center, version).
			addComponent<gui_framework::Button>(L"AddConfiguration", 150, 40, DialogBox::DialogBoxBuilder::alignment::center, add, 0, 5);

		DialogBox* dialogBox = builder.build();

		dynamic_cast<gui_framework::Button*>(dialogBox->findChild(L"AddConfiguration"))->setOnClick([dialogBox, &controller]()
			{
				try
				{
					controller->receiveData(dialogBox);
				}
				catch (const runtime_error& e)
				{
					BaseDialogBox::createMessageBox(utility::to_wstring(e.what(), CP_UTF8), L"Ошибка", BaseDialogBox::messageBoxType::ok, dialogBox);
				}
			});

		dialogBox->show();

		return dialogBox;
	}

	ProjectConfigurationView::ProjectConfigurationView(const shared_ptr<controllers::BaseController>& controller) :
		BaseView(controller, ProjectConfigurationView::createConfigurationDialog(controller), true)
	{

	}

	void ProjectConfigurationView::update(const json::JSONParser& data)
	{
		using gui_framework::BaseDialogBox;

		bool success = data.get<bool>("success");
		string message = data.get<string>("message");

		if (success)
		{
			if (BaseDialogBox::createMessageBox(utility::to_wstring(message, CP_UTF8), L"Успех", BaseDialogBox::messageBoxType::ok, dynamic_cast<gui_framework::BaseComponent*>(window)) == BaseDialogBox::messageBoxResponse::ok)
			{
				controller->getModel()->removeObserver(this);
			}
		}
		else
		{
			BaseDialogBox::createMessageBox(utility::to_wstring(message, CP_UTF8), L"Ошибка", BaseDialogBox::messageBoxType::ok, dynamic_cast<gui_framework::BaseComponent*>(window));
		}
	}
}
