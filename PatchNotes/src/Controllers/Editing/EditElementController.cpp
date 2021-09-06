#include "EditElementController.h"

#include "Components/ComboBoxes/DropDownListComboBox.h"

#include "Models/Editing/EditElementModel.h"
#include "PatchNotesUtility.h"

using namespace std;

namespace controllers
{
	json::JSONBuilder EditElementController::collectData(gui_framework::BaseComposite* window) const
	{
		uint32_t codepage = utility::getCodepage();
		gui_framework::DropDownListComboBox* projects = static_cast<gui_framework::DropDownListComboBox*>(window->findChild(L"Projects"));
		gui_framework::DropDownListComboBox* categories = static_cast<gui_framework::DropDownListComboBox*>(window->findChild(L"Categories"));
		gui_framework::DropDownListComboBox* elements = static_cast<gui_framework::DropDownListComboBox*>(window->findChild(L"Elements"));
		const wstring& newElement = static_cast<gui_framework::EditControl*>(window->findChild(L"NewElementName"))->getText();
		string project = gui_framework::utility::to_string(projects->getValue(projects->getCurrentSelectionIndex()), codepage);
		string category = gui_framework::utility::to_string(categories->getValue(categories->getCurrentSelectionIndex()), codepage);
		string element = gui_framework::utility::to_string(elements->getValue(elements->getCurrentSelectionIndex()), codepage);

		return json::JSONBuilder(codepage).
			append("project", move(project)).
			append("category", move(category)).
			append("element", move(element)).
			append("newElement", gui_framework::utility::to_string(newElement, codepage));
	}

	EditElementController::EditElementController() :
		BaseController(make_unique<models::EditElementModel>())
	{

	}
}
