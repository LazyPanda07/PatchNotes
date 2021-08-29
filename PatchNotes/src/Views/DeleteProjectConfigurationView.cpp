#include "DeleteProjectConfigurationView.h"

#include "Controllers/DeleteProjectConfigurationController.h"

using namespace std;

namespace views
{
	DeleteProjectConfigurationView::DeleteProjectConfigurationView() :
		BaseView(make_unique<controllers::DeleteProjectConfigurationController>(), nullptr)
	{

	}

	void DeleteProjectConfigurationView::update(const json::JSONParser& data)
	{

	}

	void DeleteProjectConfigurationView::onClick(gui_framework::BaseComposite* patchNotesWindow)
	{
		controller->receiveData(patchNotesWindow);
	}
}
