#include "GenerateHTMLView.h"

#include "Composites/DialogBox.h"
#include "Components/ProgressBars/ProgressBar.h"

#include "PatchNotesConstants.h"
#include "PatchNotesUtility.h"

using namespace std;

namespace views
{
	GenerateHTMLView::GenerateHTMLView(const std::shared_ptr<controllers::BaseController>& controller) :
		BaseView(controller, nullptr)
	{

	}

	void GenerateHTMLView::update(const json::JSONParser& data)
	{
		using gui_framework::BaseDialogBox;

		bool success = data.get<bool>("success");
		string message = data.get<string>("message");
		const wstring& title = success ? successTitle : errorTitle;

		BaseDialogBox::createMessageBox(utility::to_wstring(message, CP_UTF8), title, BaseDialogBox::messageBoxType::ok, dynamic_cast<gui_framework::BaseComponent*>(window));
	}

	void GenerateHTMLView::onClick(gui_framework::BaseComposite* patchNotesWindow)
	{
		controller->receiveData(patchNotesWindow);
	}
}
