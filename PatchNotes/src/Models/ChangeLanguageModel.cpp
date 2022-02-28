#include "ChangeLanguageModel.h"

#include "GUIFramework.h"

#include "PatchNotesConstants.h"
#include "PatchNotesUtility.h"

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

		ShellExecuteW(NULL, L"open", globals::pathToPatchNotes.data(), command_line::restart.data(), nullptr, SW_SHOWDEFAULT);

		exit(0);
	
		return json::JSONBuilder(CP_UTF8).
			appendBool("success", true).
			appendString("message", "Success");
	}

	void ChangeLanguageModel::changeLanguage(const string& changeTo)
	{
		json::JSONBuilder builder(gui_framework::GUIFramework::get().getJSONSettings().getParsedData(), CP_UTF8);

		builder[json_settings::language] = changeTo;

		ofstream(gui_framework::json_settings::settingsJSONFile.data()) << builder;
	}

	ChangeLanguageModel::ChangeLanguageModel(std::unique_ptr<gui_framework::WindowHolder>& mainWindow) :
		mainWindow(mainWindow)
	{

	}
}
