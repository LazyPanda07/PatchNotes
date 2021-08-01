#include "ProjectConfigurationView.h"

#include "Composites/DialogBox.h"
#include "Components/EditControl.h"

#include "Controllers/ProjectConfigurationController.h"
#include "PatchNotesUtility.h"
#include "PatchNotesConstants.h"

#include "Exceptions/ValidationException.h"

using namespace std;

CREATE_DEFAULT_WINDOW_FUNCTION(projectConfiguration)

namespace views
{
	gui_framework::BaseComposite* ProjectConfigurationView::createConfigurationDialog(const unique_ptr<controllers::BaseController>& controller)
	{
		using gui_framework::DialogBox;
		using gui_framework::BaseDialogBox;

		auto [x, y] = utility::getScreenCenter(gui_framework::standard_sizes::dialogBoxBuilderMinWidth, gui_framework::standard_sizes::dialogBoxBuilderMinHeight);

		DialogBox::DialogBoxBuilder builder(L"ProjectConfiguration", L"������������ �������", x, y, "projectConfiguration");

		gui_framework::utility::AdditionalCreationData<gui_framework::EditControl> name(L"�������� �������");
		gui_framework::utility::AdditionalCreationData<gui_framework::EditControl> version(L"������ �������");
		gui_framework::utility::AdditionalCreationData<gui_framework::Button> add(L"��������", []() {});

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
				catch (const exceptions::ValidationException& e)
				{
					BaseDialogBox::createMessageBox(e.getMessage(), errorTitle, BaseDialogBox::messageBoxType::ok, dialogBox);
				}
			});

		dialogBox->show();

		return dialogBox;
	}

	ProjectConfigurationView::ProjectConfigurationView(unique_ptr<controllers::BaseController>& patchNotesController) :
		BaseView(make_unique<controllers::ProjectConfigurationController>(), ProjectConfigurationView::createConfigurationDialog(controller), true),
		patchNotesController(patchNotesController)
	{
		
	}

	void ProjectConfigurationView::update(const json::JSONParser& data)
	{
		patchNotesController->getModel()->getObservers().back()->update(data);
	}
}
