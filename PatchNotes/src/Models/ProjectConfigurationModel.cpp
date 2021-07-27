#include "ProjectConfigurationModel.h"

#include <filesystem>

#include "PatchNotesConstants.h"
#include "PatchNotesUtility.h"

using namespace std;

namespace models
{
	ProjectConfigurationModel::ProjectConfigurationModel(const shared_ptr<views::interfaces::IObserver>& projectConfigurationView)
	{
		this->addObserver(projectConfigurationView);
	}

	json::JSONBuilder ProjectConfigurationModel::processData(const json::JSONParser& data)
	{
		json::JSONBuilder builder(utility::getCodepage());
		bool success = true;
		string message;
		const string& projectName = data.get<string>("projectName");
		const string& projectVersion = data.get<string>("projectVersion");

		filesystem::path projectFile(filesystem::path(dataFolder) /= filesystem::path(projectName + '_' + projectVersion) /= ".json");

		if (filesystem::exists(projectFile))
		{
			success = false;

			builder.append("message", format("Файл с названием {} и версией {} уже существует", projectName, projectVersion));
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
