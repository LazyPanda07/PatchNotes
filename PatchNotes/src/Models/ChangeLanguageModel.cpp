#include "ChangeLanguageModel.h"

#include "PatchNotesConstants.h"

using namespace std;

namespace models
{
	json::JSONBuilder ChangeLanguageModel::processData(const json::JSONParser& data)
	{
		const string& language = data.getString(json_settings::language);

		if (language == "ru")
		{
			this->changeLanguage("en");
		}
		else if (language == "en")
		{
			this->changeLanguage("ru");
		}
		else
		{
			return json::JSONBuilder(CP_UTF8).
				appendBool("success", false).
				appendString("message", "Wrong language");
		}
	
		return json::JSONBuilder(CP_UTF8).
			appendBool("success", true).
			appendString("message", "Success");
	}

	void ChangeLanguageModel::changeLanguage(const string& changeTo)
	{
		auto& instance = gui_framework::GUIFramework::get();

		json::JSONBuilder builder(instance.getJSONSettings().getParsedData(), CP_UTF8);

		builder[json_settings::language] = changeTo;

		ofstream(gui_framework::json_settings::settingsJSONFile.data()) << builder;

		const_cast<json::JSONParser&>(instance.getJSONSettings()) = json::JSONParser(ifstream(gui_framework::json_settings::settingsJSONFile.data()));
	}

	ChangeLanguageModel::ChangeLanguageModel(std::unique_ptr<gui_framework::WindowHolder>& mainWindow) :
		mainWindow(mainWindow)
	{

	}
}
