#include "GenerateHTMLView.h"

#include "Composites/DialogBox.h"
#include "Components/ProgressBars/ProgressBar.h"

#include "Controllers/GenerateHTMLController.h"
#include "PatchNotesConstants.h"
#include "PatchNotesUtility.h"

using namespace std;

namespace views
{
	GenerateHTMLView::GenerateHTMLView(gui_framework::BaseComposite* mainWindow) :
		BaseView(make_unique<controllers::GenerateHTMLController>(mainWindow), nullptr),
		mainWindow(mainWindow)
	{

	}

	void GenerateHTMLView::update(const json::JSONParser& data)
	{
		using gui_framework::BaseDialogBox;

		bool success = data.get<bool>("success");
		string message = data.get<string>("message");
		const wstring& title = success ? successTitle : errorTitle;
		gui_framework::ProgressBar* updateProgressBar = dynamic_cast<gui_framework::ProgressBar*>(dynamic_cast<gui_framework::BaseComposite*>(mainWindow->findChild(L"PatchNotesUI"))->findChild(L"GenerateHTMLProgressBar"));

		if (BaseDialogBox::createMessageBox(utility::to_wstring(message, CP_UTF8), title, BaseDialogBox::messageBoxType::ok, dynamic_cast<gui_framework::BaseComponent*>(window)) == BaseDialogBox::messageBoxResponse::ok)
		{
			updateProgressBar->update(0);
		}
	}

	void GenerateHTMLView::onClick(gui_framework::BaseComposite* patchNotesWindow)
	{
		controller->receiveData(patchNotesWindow);
	}
}
