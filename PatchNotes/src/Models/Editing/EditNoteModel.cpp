#include "EditNoteModel.h"

#include "PatchNotesConstants.h"
#include "PatchNotesUtility.h"

using namespace std;

namespace models
{
	json::JSONBuilder EditNoteModel::processData(const json::JSONParser& data)
	{
		uint32_t codepage = utility::getCodepage();
		json::JSONBuilder builder(codepage);
		filesystem::path pathToProject = filesystem::path(globals::dataFolder) /= data.getString("project") + ".json";
		json::JSONParser projectConfiguration = ifstream(pathToProject);
		const string& category = data.getString("category");
		const string& element = data.getString("element");
		const string& note = data.getString("note");
		const string& newNote = data.getString("newNote");
		bool success = true;
		string message;
		json::utility::jsonObject& parsedData = const_cast<json::utility::jsonObject&>(projectConfiguration.getParsedData());

		for (auto& i : parsedData.data)
		{
			if (i.first == category)
			{
				auto& categoryObject = get<json::utility::objectSmartPointer<json::utility::jsonObject>>(i.second);

				for (auto& j : categoryObject->data)
				{
					if (j.first == element)
					{
						auto& elementObject = get<json::utility::objectSmartPointer<json::utility::jsonObject>>(j.second);

						for (auto& k : elementObject->data)
						{
							if (k.second.index() == static_cast<size_t>(json::utility::variantTypeEnum::jJSONArray))
							{
								auto& notes = get<vector<json::utility::objectSmartPointer<json::utility::jsonObject>>>(k.second);

								for (auto& value : notes)
								{
									if (get<string>(value->data.front().second) == note)
									{
										value->data.pop_back();

										value->data.push_back({ ""s, newNote });

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

		ofstream(pathToProject) << projectConfiguration;

		message = format(R"(�������� \"{}\" ���� �������� �� \"{}\")", json::utility::fromUTF8JSON(note, codepage), json::utility::fromUTF8JSON(newNote, codepage));

		builder.
			append("success", true).
			append("message", move(message));

		return builder;
	}
}
