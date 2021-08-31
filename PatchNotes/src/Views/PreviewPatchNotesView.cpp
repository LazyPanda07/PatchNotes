#include "PreviewPatchNotesView.h"

#include "Components/ProgressBars/ProgressBar.h"

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
		string pathToFile = data.getString("pathToFile");
		gui_framework::ProgressBar* updateProgressBar = static_cast<gui_framework::ProgressBar*>(static_cast<gui_framework::BaseComposite*>(mainWindow->findChild(L"PatchNotesUI"))->findChild(L"GenerateHTMLProgressBar"));

		if (data.getBool("success"))
		{
			updateProgressBar->update(0);

			system(format("start \"{}\"", pathToFile).data());

			Initializer::get().addPreviewFile(pathToFile);
		}
	}

	void PreviewPatchNotesView::onClick(gui_framework::BaseComposite* patchNotesWindow)
	{
		controller->receiveData(patchNotesWindow);
	}
}
