#include "DeleteNoteModel.h"

#include <filesystem>

#include "JSONArrayWrapper.h"

#include "PatchNotesUtility.h"

using namespace std;

namespace models
{
	json::JSONBuilder DeleteNoteModel::processData(const json::JSONParser& data)
	{
		const string& pathToProject = data.getString("pathToProject");
		const string& category = data.getString("category");
		const string& element = data.getString("element");
		string noteToDelete = data.getString("noteToDelete");
		json::JSONParser json = (ifstream(pathToProject));
		const vector<pair<string, json::utility::jsonObject::variantType>>& parsedData = json.getParsedData().data;

		for (size_t i = 0; i < parsedData.size(); i++)
		{
			if (parsedData[i].first == category)
			{
				const vector<pair<string, json::utility::jsonObject::variantType>>& jsonCategory = get<json::utility::objectSmartPointer<json::utility::jsonObject>>(parsedData[i].second)->data;

				for (size_t j = 0; j < jsonCategory.size(); j++)
				{
					if (jsonCategory[j].first == element)
					{
						const vector<pair<string, json::utility::jsonObject::variantType>>& jsonElement = get<json::utility::objectSmartPointer<json::utility::jsonObject>>(jsonCategory[j].second)->data;

						for (size_t k = 0; k < jsonElement.size(); k++)
						{
							if (jsonElement[k].second.index() == static_cast<size_t>(json::utility::variantTypeEnum::jJSONArray))
							{
								const vector<json::utility::objectSmartPointer<json::utility::jsonObject>>& notes = get<vector<json::utility::objectSmartPointer<json::utility::jsonObject>>>(jsonElement[k].second);

								for (size_t noteIndex = 0; noteIndex < notes.size(); noteIndex++)
								{
									if (get<string>(notes[noteIndex]->data.front().second) == noteToDelete)
									{
										const_cast<vector<json::utility::objectSmartPointer<json::utility::jsonObject>>&>(notes).erase(notes.begin() + noteIndex);

										break;
									}
								}

								break;
							}
						}

						break;
					}
				}

				break;
			}
		}

		ofstream(pathToProject) << json;

		return json::JSONBuilder(utility::getCodepage()).
			append("success", true).
			append("message", format("Описание {} было успешно удалено", move(noteToDelete)));
	}
}
