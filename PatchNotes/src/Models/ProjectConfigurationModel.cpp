#include "ProjectConfigurationModel.h"

#include <filesystem>
#include <fstream>

#include "PatchNotesConstants.h"
#include "PatchNotesUtility.h"

using namespace std;

namespace models
{
	json::JSONBuilder ProjectConfigurationModel::processData(const json::JSONParser& data)
	{
		using json::utility::toUTF8JSON;
		using json::utility::fromUTF8JSON;

		json::JSONBuilder builder(CP_UTF8);
		bool success = true;
		string message;
		string projectName = data.getString("projectName");
		string projectVersion = data.getString("projectVersion");
		localization::TextLocalization& textLocalization = localization::TextLocalization::get();

		filesystem::path projectFile(filesystem::path(globals::dataFolder) /= projectName + '_' + projectVersion + ".json");

		if (filesystem::exists(projectFile))
		{
			success = false;

			message = format(textLocalization[patch_notes_localization::fileAlreadyExists], projectName + '_' + projectVersion + ".json");
		}
		else
		{
			json::JSONBuilder projectData(CP_UTF8);

			projectData.
				append("projectName", projectName).
				append("projectVersion", projectVersion);

			ofstream(projectFile) << projectData;

			message = format(textLocalization[patch_notes_localization::configurationSuccessfullyAdded], projectName + '_' + projectVersion);
		}

		builder.
			append("success", success).
			append("message", move(message));

		return builder;
	}
}
