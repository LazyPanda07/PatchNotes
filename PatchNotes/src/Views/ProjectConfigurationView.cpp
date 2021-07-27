#include "ProjectConfigurationView.h"

#include "Composites/DialogBox.h"
#include "Components/EditControl.h"

#include "PatchNotesUtility.h"

using namespace std;

namespace views
{
	unique_ptr<gui_framework::BaseComposite> ProjectConfigurationView::createConfigurationDialog()
	{
		using gui_framework::DialogBox;
		using gui_framework::BaseDialogBox;

		uint16_t width = 600;
		uint16_t height = 400;

		auto [x, y] = utility::getScreenCenter(width, height);

		DialogBox::DialogBoxBuilder builder(L"ProjectConfiguration", L"Конфигурация проекта", x, y, "projectConfiguration");

		gui_framework::utility::AdditionalCreationData<gui_framework::EditControl> name(L"Название проекта");
		gui_framework::utility::AdditionalCreationData<gui_framework::EditControl> version(L"Версия проекта");
		gui_framework::utility::AdditionalCreationData<gui_framework::Button> submit(L"Версия проекта", []() { BaseDialogBox::createMessageBox(L"Text", L"Title", BaseDialogBox::messageBoxType::ok); });

		builder.
			addComponent<gui_framework::EditControl>(L"ProjectName", 200, 20, DialogBox::DialogBoxBuilder::alignment::center, name).
			addComponent<gui_framework::EditControl>(L"ProjectVersion", 200, 20, DialogBox::DialogBoxBuilder::alignment::center, version).
			addComponent<gui_framework::Button>(L"Submit", 200, 20, DialogBox::DialogBoxBuilder::alignment::left);

		return unique_ptr<gui_framework::BaseComposite>(builder.build());
	}

	ProjectConfigurationView::ProjectConfigurationView(const shared_ptr<controllers::BaseController>& controller) :
		BaseView(controller, ProjectConfigurationView::createConfigurationDialog())
	{

	}

	void ProjectConfigurationView::update(const json::JSONParser& data)
	{

	}

	ProjectConfigurationView::~ProjectConfigurationView()
	{

	}
}
