#include "GenerateHTMLView.h"

#include "Components/ProgressBars/ProgressBar.h"

using namespace std;

namespace views
{
	GenerateHTMLView::GenerateHTMLView(const std::shared_ptr<controllers::BaseController>& controller) :
		BaseView(controller, nullptr)
	{

	}

	void GenerateHTMLView::update(const json::JSONParser& data)
	{

	}

	void GenerateHTMLView::onClick(gui_framework::BaseComposite* patchNotesWindow)
	{
		controller->receiveData(patchNotesWindow);
	}
}
