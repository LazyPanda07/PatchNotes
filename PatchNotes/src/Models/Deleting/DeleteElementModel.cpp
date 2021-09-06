#include "DeleteElementModel.h"

#include <filesystem>

#include "PatchNotesUtility.h"

using namespace std;

namespace models
{
	json::JSONBuilder DeleteElementModel::processData(const json::JSONParser& data)
	{
		const string& pathToProject = data.getString("pathToProject");
		const string& category = data.getString("category");
		string elementToDelete = data.getString("elementToDelete");
		json::JSONParser json = (ifstream(pathToProject));
		const vector<pair<string, json::utility::jsonObject::variantType>>& parsedData = json.getParsedData().data;

		for (size_t i = 0; i < parsedData.size(); i++)
		{
			if (parsedData[i].first == category)
			{
				const vector<pair<string, json::utility::jsonObject::variantType>>& jsonCategory = get<json::utility::objectSmartPointer<json::utility::jsonObject>>(parsedData[i].second)->data;

				for (size_t j = 0; j < jsonCategory.size(); j++)
				{
					if (jsonCategory[j].first == elementToDelete)
					{
						const_cast<vector<pair<string, json::utility::jsonObject::variantType>>&>(jsonCategory).erase(jsonCategory.begin() + j);

						break;
					}
				}

				break;
			}
		}

		ofstream(pathToProject) << json;

		return json::JSONBuilder(utility::getCodepage()).
			append("success", true).
			append("message", format(R"(������� \"{}\" ��� ������� ������)", move(elementToDelete)));
	}
}
