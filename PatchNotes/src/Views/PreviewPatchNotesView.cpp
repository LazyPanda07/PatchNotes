#include "PreviewPatchNotesView.h"

#include "Components/ProgressBars/ProgressBar.h"

#include "Composites/DialogBox.h"
#include "Initializer.h"
#include "Controllers/PreviewPatchNotesController.h"
#include "PatchNotesConstants.h"
#include "PatchNotesUtility.h"

using namespace std;

namespace views
{
	PreviewPatchNotesView::PreviewPatchNotesView(gui_framework::BaseComposite* mainWindow) :
		BaseView(make_unique<controllers::PreviewPatchNotesController>(mainWindow), nullptr),
		mainWindow(mainWindow)
	{

	}

	void PreviewPatchNotesView::update(const json::JSONParser& data)
	{
		using gui_framework::BaseDialogBox;

		string pathToFile = data.getString("pathToFile");

		if (data.getBool("success"))
		{
			system(format("\"{}\"", pathToFile).data());

			static_cast<gui_framework::ProgressBar*>(static_cast<gui_framework::BaseComposite*>(mainWindow->findChild(L"PatchNotesUI"))->findChild(L"GenerateHTMLProgressBar"))->update(0);

			Initializer::get().addPreviewFile(pathToFile);
		}
		else
		{
			BaseDialogBox::createMessageBox(utility::to_wstring(data.getString("message"), CP_UTF8), patch_notes_constants::errorTitle, BaseDialogBox::messageBoxType::ok, static_cast<gui_framework::BaseComponent*>(window));
		}
	}

	void PreviewPatchNotesView::onClick(gui_framework::BaseComposite* patchNotesWindow)
	{
		controller->receiveData(patchNotesWindow);
	}
}
