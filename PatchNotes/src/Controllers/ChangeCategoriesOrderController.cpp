#include "ChangeCategoriesOrderController.h"

#include "Models/ChangeCategoriesOrderModel.h"
#include "PatchNotesUtility.h"

using namespace std;

namespace controllers
{
	json::JSONBuilder ChangeCategoriesOrderController::collectData(gui_framework::BaseComposite* window) const
	{
		uint32_t codepage = utility::getCodepage();
		gui_framework::StaticControl* projectConfiguration = static_cast<gui_framework::StaticControl*>(window->findChild(L"ProjectConfiguration"));
		wistringstream split(static_cast<gui_framework::RichEdit*>(window->findChild(L"Categories"))->getText());
		vector<json::utility::objectSmartPointer<json::utility::jsonObject>> categories;
		string currentProject = gui_framework::utility::to_string(projectConfiguration->getText(), codepage);
		wstring tem;

		categories.reserve(ranges::count(split.str(), L'\r') + 1);

		while (getline(split, tem, L'\r'))
		{
			erase(tem, L'\n');

			json::utility::appendArray(gui_framework::utility::to_string(tem, codepage), categories);
		}

		return json::JSONBuilder(codepage).
			append("project", move(currentProject)).
			append("categories", move(categories));
	}

	ChangeCategoriesOrderController::ChangeCategoriesOrderController() :
		BaseController(make_unique<models::ChangeCategoriesOrderModel>())
	{

	}
}
