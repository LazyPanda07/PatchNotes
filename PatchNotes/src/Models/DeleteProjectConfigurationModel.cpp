#include "DeleteProjectConfigurationModel.h"

#include <filesystem>

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
			message = format("������������ {} ���� ������� �������", projectToDelete.filename().stem().string());
		}
		else
		{
			message = format("�� ������� ������� {}", projectToDelete.filename().stem().string());
		}

		return json::JSONBuilder(1251).
			append("success", success).
			append("message", move(message));
	}
}
