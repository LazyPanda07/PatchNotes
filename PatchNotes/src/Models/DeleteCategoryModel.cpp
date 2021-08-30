#include "DeleteCategoryModel.h"

#include <filesystem>

#include "PatchNotesUtility.h"

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

		return json::JSONBuilder(utility::getCodepage()).
			append("success", true).
			append("message", format("Категория {} была успешно удалена", move(categoryToDelete)));
	}
}
