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

		uint32_t codepage = utility::getCodepage();
		json::JSONBuilder builder(CP_UTF8);
		bool success = true;
		string message;
		const string& projectName = data.get<string>("projectName");
		const string& projectVersion = data.get<string>("projectVersion");

		filesystem::path projectFile(filesystem::path(dataFolder) /= projectName + '_' + projectVersion + ".json");

		if (filesystem::exists(projectFile))
		{
			success = false;

			message = toUTF8JSON(R"(Файл с названием ")", codepage) + projectName + toUTF8JSON(R"(" и версией ")", codepage) + projectVersion + toUTF8JSON(R"(" уже существует)", codepage);
		}
		else
		{
			json::JSONBuilder projectData(utility::getCodepage());

			projectData.
				append("projectName", projectName).
				append("projectVersion", projectVersion);

			ofstream(projectFile) << projectData;

			message = toUTF8JSON("Конфигурация успешно создана", codepage);
		}

		builder.
			append("success", success).
			append("message", move(message));

		return builder;
	}
}
