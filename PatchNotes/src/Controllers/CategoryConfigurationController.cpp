#include "CategoryConfigurationController.h"

#include "Models/CategoryConfigurationModel.h"
#include "PatchNotesUtility.h"
#include "Validation.h"

using namespace std;

namespace controllers
{
	json::JSONBuilder CategoryConfigurationController::collectData(gui_framework::BaseComposite* window) const
	{
		uint32_t codepage = utility::getCodepage();
		json::JSONBuilder builder(codepage);
		gui_framework::EditControl* categoryEditControl = dynamic_cast<gui_framework::EditControl*>(window->findChild(L"CategoryName"));
		string projectFile = gui_framework::utility::to_string(dynamic_cast<gui_framework::StaticControl*>(window->findChild(L"ProjectCategory"))->getText(), codepage);
		string categoryName = gui_framework::utility::to_string(categoryEditControl->getText(), codepage);

		validation::emptyValidation(categoryName, categoryEditControl->getPlaceholder());

		builder.
			append("projectFile", move(projectFile)).
			append("category", move(categoryName));

		return builder;
	}

	CategoryConfigurationController::CategoryConfigurationController() :
		BaseController(make_unique<models::CategoryConfigurationModel>())
	{

	}
}
