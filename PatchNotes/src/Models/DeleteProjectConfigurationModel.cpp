#include "DeleteProjectConfigurationModel.h"

#include <filesystem>

using namespace std;

namespace models
{
	json::JSONBuilder DeleteProjectConfigurationModel::processData(const json::JSONParser& data)
	{
		filesystem::path projectToDelete = data.getString("projectToDelete");

		filesystem::remove(projectToDelete);

		return json::JSONBuilder(1251).
			append("success", true).
			append("message", format("Конфигурация {} была успешно удалена", projectToDelete.filename().stem().string()));
	}
}
