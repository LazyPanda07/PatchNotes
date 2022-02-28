#include "GenerateHTMLController.h"

#include "ComponentsHeader.h"

#include "Models/GenerateHTMLModel.h"
#include "PatchNotesUtility.h"
#include "PatchNotesConstants.h"

#include "Exceptions/ValidationException.h"

using namespace std;

namespace controllers
{
	json::JSONBuilder GenerateHTMLController::collectData(gui_framework::BaseComposite* window) const
	{
		json::JSONBuilder builder(CP_UTF8);
		gui_framework::DropDownListComboBox* currentProject = static_cast<gui_framework::DropDownListComboBox*>(window->findChild(L"ProjectNameAndVersion"));

		if (currentProject->getCurrentSelectionIndex() == -1)
		{
			throw exceptions::ValidationException(localization::WTextLocalization::get()[patch_notes_localization::failedToFindProject]);
		}

		builder.
			append("projectFile", gui_framework::utility::to_string(currentProject->getValue(currentProject->getCurrentSelectionIndex()), CP_UTF8));

		return builder;
	}

	GenerateHTMLController::GenerateHTMLController(gui_framework::BaseComposite* mainWindow) :
		BaseController(make_unique<models::GenerateHTMLModel>(mainWindow))
	{

	}
}
