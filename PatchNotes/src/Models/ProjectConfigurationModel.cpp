#include "ProjectConfigurationModel.h"

#include <filesystem>

#include "PatchNotesConstants.h"
#include "PatchNotesUtility.h"

using namespace std;

namespace models
{
	json::JSONBuilder ProjectConfigurationModel::processData(const json::JSONParser& data)
	{
		using json::utility::toUTF8JSON;
		using json::utility::fromUTF8JSON;

		uint32_t codepage = utility::getCodepage();
		json::JSONBuilder builder(codepage);
		bool success = true;
		string message;
		string projectName = fromUTF8JSON(data.getString("projectName"), codepage);
		string projectVersion = fromUTF8JSON(data.getString("projectVersion"), codepage);

		filesystem::path projectFile(filesystem::path(globals::dataFolder) /= projectName + '_' + projectVersion + ".json");

		if (filesystem::exists(projectFile))
		{
			success = false;

			message = format("Файл с названием \"{}.json\" уже существует", projectName + '_' + projectVersion);
		}
		else
		{
			json::JSONBuilder projectData(utility::getCodepage());

			projectData.
				append("projectName", projectName).
				append("projectVersion", projectVersion);

			ofstream(projectFile) << projectData;

			message = "Конфигурация успешно создана";
		}

		builder.
			append("success", success).
			append("message", move(message));

		return builder;
	}
}
