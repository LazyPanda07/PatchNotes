#include "ChangeLanguageView.h"

#include "CompositesHeader.h"
#include "Controllers/ChangeLanguageController.h"
#include "PatchNotesConstants.h"
#include "PatchNotesUtility.h"

using namespace std;

namespace views
{
	ChangeLanguageView::ChangeLanguageView(gui_framework::BaseComponent* parent, unique_ptr<gui_framework::WindowHolder>& mainWindow) :
		BaseView(make_unique<controllers::ChangeLanguageController>(mainWindow), nullptr)
	{

	}

	void ChangeLanguageView::update(const json::JSONParser& data)
	{
		using gui_framework::BaseDialogBox;
		const string& message = data.getString("message");

		if (data.getBool("success"))
		{
			BaseDialogBox::createMessageBox(utility::to_wstring(message, CP_UTF8), patch_notes_constants::successTitle, BaseDialogBox::messageBoxType::ok, nullptr);
		}
		else
		{
			BaseDialogBox::createMessageBox(utility::to_wstring(message, CP_UTF8), patch_notes_constants::errorTitle, BaseDialogBox::messageBoxType::ok, nullptr);
		}
	}

	void ChangeLanguageView::onClick()
	{
		controller->receiveData(nullptr);
	}
}
