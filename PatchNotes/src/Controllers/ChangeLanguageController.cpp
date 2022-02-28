#include "ChangeLanguageController.h"

#include "GUIFramework.h"

#include "Models/ChangeLanguageModel.h"
#include "PatchNotesConstants.h"

using namespace std;

namespace controllers
{
	json::JSONBuilder ChangeLanguageController::collectData(gui_framework::BaseComposite* window) const
	{
		const string& language = gui_framework::GUIFramework::get().getJSONSettings().getString(json_settings::language);

		return json::JSONBuilder(CP_UTF8).
			appendString(json_settings::language, language);
	}

	ChangeLanguageController::ChangeLanguageController(unique_ptr<gui_framework::WindowHolder>& mainWindow) :
		BaseController(make_unique<models::ChangeLanguageModel>(mainWindow))
	{

	}
}
