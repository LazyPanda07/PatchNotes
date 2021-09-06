#include "DeleteProjectConfigurationModel.h"

#include <filesystem>

#include "PatchNotesUtility.h"

using namespace std;

namespace models
{
	json::JSONBuilder DeleteProjectConfigurationModel::processData(const json::JSONParser& data)
	{
		filesystem::path projectToDelete = data.getString("projectToDelete");
		string message;
		bool success = filesystem::remove(projectToDelete);

		if (success)
		{
			message = format(R"(Конфигурация \"{}\" была успешно удалена)", projectToDelete.filename().stem().string());
		}
		else
		{
			message = format(R"(Не удалось удалить конфигурацию \"{}\")", projectToDelete.filename().stem().string());
		}

		return json::JSONBuilder(utility::getCodepage()).
			append("success", success).
			append("message", move(message));
	}
}
