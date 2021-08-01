#include "GenerateHTMLController.h"

#include "Models/GenerateHTMLModel.h"
#include "PatchNotesUtility.h"

#include "Exceptions/ValidationException.h"

using namespace std;

namespace controllers
{
	json::JSONBuilder GenerateHTMLController::collectData(gui_framework::BaseComposite* window) const
	{
		json::JSONBuilder builder(utility::getCodepage());
		gui_framework::DropDownListComboBox* currentProject = dynamic_cast<gui_framework::DropDownListComboBox*>(window->findChild(L"ProjectNameAndVersion"));

		if (currentProject->getCurrentSelectionIndex() == -1)
		{
			throw exceptions::ValidationException("Не удалось определить проект");
		}

		builder.
			append("projectFile", gui_framework::utility::to_string(currentProject->getValue(currentProject->getCurrentSelectionIndex()), utility::getCodepage()));

		return builder;
	}

	GenerateHTMLController::GenerateHTMLController(gui_framework::BaseComposite* mainWindow) :
		BaseController(make_unique<models::GenerateHTMLModel>(mainWindow))
	{

	}
}
