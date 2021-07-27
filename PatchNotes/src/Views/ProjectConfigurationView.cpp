#include "ProjectConfigurationView.h"

#include "Composites/DialogBox.h"
#include "Components/EditControl.h"

#include "PatchNotesUtility.h"

using namespace std;

CREATE_DEFAULT_WINDOW_FUNCTION(projectConfiguration)

namespace views
{
	unique_ptr<gui_framework::BaseComposite> ProjectConfigurationView::createConfigurationDialog(const shared_ptr<controllers::BaseController>& controller)
	{
		using gui_framework::DialogBox;
		using gui_framework::BaseDialogBox;

		auto [x, y] = utility::getScreenCenter(gui_framework::standard_sizes::dialogBoxBuilderMinWidth, gui_framework::standard_sizes::dialogBoxBuilderMinHeight);

		DialogBox::DialogBoxBuilder builder(L"ProjectConfiguration", L"Конфигурация проекта", x, y, "projectConfiguration");

		gui_framework::utility::AdditionalCreationData<gui_framework::EditControl> name(L"Название проекта");
		gui_framework::utility::AdditionalCreationData<gui_framework::EditControl> version(L"Версия проекта");
		gui_framework::utility::AdditionalCreationData<gui_framework::Button> add(L"Добавить", []() {  });

		builder.
			addComponent<gui_framework::EditControl>(L"ProjectName", 200, 20, DialogBox::DialogBoxBuilder::alignment::center, name).
			addComponent<gui_framework::EditControl>(L"ProjectVersion", 200, 20, DialogBox::DialogBoxBuilder::alignment::center, version).
			addComponent<gui_framework::Button>(L"Add", 150, 40, DialogBox::DialogBoxBuilder::alignment::center, add, 0, 5);

		DialogBox* dialogBox = builder.build();

		dynamic_cast<gui_framework::Button*>(dialogBox->findChild(L"Add"))->setOnClick([dialogBox, &controller]() { controller->receiveData(dialogBox); });

		dialogBox->show();

		return unique_ptr<gui_framework::BaseComposite>(dialogBox);
	}

	ProjectConfigurationView::ProjectConfigurationView(const shared_ptr<controllers::BaseController>& controller) :
		BaseView(controller, ProjectConfigurationView::createConfigurationDialog(controller))
	{

	}

	void ProjectConfigurationView::update(const json::JSONParser& data)
	{

	}

	ProjectConfigurationView::~ProjectConfigurationView()
	{
		
	}
}
