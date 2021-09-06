#include "EditCategoryModel.h"

#include "PatchNotesUtility.h"
#include "PatchNotesConstants.h"

using namespace std;

namespace models
{
	json::JSONBuilder EditCategoryModel::processData(const json::JSONParser& data)
	{
		uint32_t codepage = utility::getCodepage();
		json::JSONBuilder builder(codepage);
		const string& project = data.getString("project");
		const string& category = data.getString("category");
		const string& newCategory = data.getString("newCategory");
		bool success = true;
		string message = format(R"(Категория \"{}\" изменена на \"{}\")", json::utility::fromUTF8JSON(category, codepage), json::utility::fromUTF8JSON(newCategory, codepage));
		filesystem::path pathToProject = filesystem::path(globals::dataFolder) /= project + ".json";
		json::JSONParser projectConfiguration = ifstream(pathToProject);
		json::utility::jsonObject& parsedData = const_cast<json::utility::jsonObject&>(projectConfiguration.getParsedData());

		for (auto& i : parsedData.data)
		{
			if (i.first == category)
			{
				i.first = newCategory;

				break;
			}
		}

		ofstream(pathToProject) << projectConfiguration;

		builder.
			append("success", success).
			append("message", move(message));

		return builder;
	}
}
