#include "EditCategoryModel.h"

#include <fstream>

#include "PatchNotesUtility.h"
#include "PatchNotesConstants.h"

using namespace std;

namespace models
{
	json::JSONBuilder EditCategoryModel::processData(const json::JSONParser& data)
	{
		json::JSONBuilder builder(CP_UTF8);
		const string& project = data.getString("project");
		const string& category = data.getString("category");
		const string& newCategory = data.getString("newCategory");
		bool success = true;
		localization::TextLocalization& textLocalization = localization::TextLocalization::get();
		string message = format(textLocalization[patch_notes_localization::categoryChanged], category, newCategory);
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
