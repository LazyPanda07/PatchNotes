#include "DeleteCategoryModel.h"

#include <filesystem>

#include "headers.h"
#include "PatchNotesUtility.h"
#include "PatchNotesConstants.h"

using namespace std;

namespace models
{
	json::JSONBuilder DeleteCategoryModel::processData(const json::JSONParser& data)
	{
		const string& pathToProject = data.getString("pathToProject");
		string categoryToDelete = data.getString("categoryToDelete");
		json::JSONParser json = (ifstream(pathToProject));
		const vector<pair<string, json::utility::jsonObject::variantType>>& parsedData = json.getParsedData().data;

		for (size_t i = 0; i < parsedData.size(); i++)
		{
			if (parsedData[i].first == categoryToDelete)
			{
				const_cast<vector<pair<string, json::utility::jsonObject::variantType>>&>(parsedData).erase(parsedData.begin() + i);

				break;
			}
		}

		ofstream(pathToProject) << json;

		return json::JSONBuilder(CP_UTF8).
			append("success", true).
			append("message", format(localization::TextLocalization::get()[patch_notes_localization::categorySuccessfullyDeleted], move(categoryToDelete)));
	}
}
