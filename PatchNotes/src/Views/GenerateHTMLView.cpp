#include "GenerateHTMLView.h"

#include "Composites/DialogBox.h"
#include "Components/ProgressBars/ProgressBar.h"

#include "Controllers/GenerateHTMLController.h"
#include "Initializer.h"
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
		string message = data.getString("message");

		if (data.getBool("success"))
		{
			if (BaseDialogBox::createMessageBox(utility::to_wstring(message, CP_UTF8), patch_notes_constants::successTitle, BaseDialogBox::messageBoxType::ok, static_cast<gui_framework::BaseComponent*>(window)) == BaseDialogBox::messageBoxResponse::ok)
			{
				static_cast<gui_framework::ProgressBar*>(static_cast<gui_framework::BaseComposite*>(mainWindow->findChild(L"PatchNotesUI"))->findChild(L"GenerateHTMLProgressBar"))->update(0);
			}
		}
		else
		{
			if (BaseDialogBox::createMessageBox(utility::to_wstring(message, CP_UTF8), patch_notes_constants::errorTitle, BaseDialogBox::messageBoxType::retryCancel, static_cast<gui_framework::BaseComponent*>(window)) == BaseDialogBox::messageBoxResponse::retry)
			{
				Initializer::get().generateHTML();
			}
		}	
	}

	void GenerateHTMLView::onClick(gui_framework::BaseComposite* patchNotesWindow)
	{
		controller->receiveData(patchNotesWindow);
	}
}
