#include "PatchNotesModel.h"

#include "pch.h"

#include "PatchNotesUtility.h"
#include "PatchNotesConstants.h"

using namespace std;

namespace models
{
	json::JSONBuilder PatchNotesModel::processData(const json::JSONParser& data)
	{
		using json::utility::objectSmartPointer;
		using json::utility::jsonObject;
		using json::utility::variantTypeEnum;

		json::JSONBuilder updateBuilder(utility::getCodepage());
		json::JSONBuilder builder(utility::getCodepage());
		filesystem::path pathToProjectFile;
		json::JSONParser projectFile;
		const string& itemName = data.get<string>("item");
		const string& categoryName = data.get<string>("category");
		const vector<objectSmartPointer<jsonObject>>& notes = data.get<vector<objectSmartPointer<jsonObject>>>("notes");
		bool success = true;
		string message = format(R"(Элемент "{}" успешно добавлен)", itemName);
		const string& projectNameAndVersion = data.get<string>("projectFile");

		pathToProjectFile.append(dataFolder).append(projectNameAndVersion) += ".json";

		ifstream(pathToProjectFile) >> projectFile;

		updateBuilder.
			append("projectName"s, projectNameAndVersion.substr(0, projectNameAndVersion.rfind('_'))).
			append("projectVersion"s, projectNameAndVersion.substr(projectNameAndVersion.rfind('_') + 1));

		try
		{
			for (const auto& i : projectFile)
			{
				if (static_cast<variantTypeEnum>(i->second.index()) == variantTypeEnum::jJSONObject)
				{
					const objectSmartPointer<jsonObject>& object = get<objectSmartPointer<jsonObject>>(i->second);
					const string& type = get<string>(find_if(object->data.begin(), object->data.end(), [](const pair<string, jsonObject::variantType>& value) { return value.first == "type"; })->second);

					if (type == "category")
					{
						objectSmartPointer<jsonObject> newObject = json::utility::make_object<jsonObject>();

						newObject->data.push_back({ "type"s, "category"s });

						for (const auto& j : object->data)
						{
							if (static_cast<variantTypeEnum>(j.second.index()) == variantTypeEnum::jJSONObject)
							{
								if (j.first == itemName && i->first == categoryName)
								{
									throw runtime_error("Элемент с таким названием уже существует");
								}

								const objectSmartPointer<jsonObject>& item = get<objectSmartPointer<jsonObject>>(j.second);
								const vector<objectSmartPointer<jsonObject>>& notes = get<vector<objectSmartPointer<jsonObject>>>(
									find_if(item->data.begin(), item->data.end(), [](const pair<string, jsonObject::variantType>& value) { return value.first == "notes"; })->second
									);
								objectSmartPointer<jsonObject> newItem = json::utility::make_object<jsonObject>();
								vector<objectSmartPointer<jsonObject>> newNotes;

								for (const auto& k : notes)
								{
									string data = json::utility::fromUTF8JSON(get<string>(k->data.back().second), utility::getCodepage());

									json::utility::appendArray(move(data), newNotes);
								}

								newItem->data.push_back({ "type"s, "item"s });

								newItem->data.push_back({ "notes"s, move(newNotes) });

								newObject->data.push_back({ j.first, move(newItem) });
							}
						}

						if (i->first == categoryName)
						{
							objectSmartPointer<jsonObject> userObject = json::utility::make_object<jsonObject>();
							vector<smartPointerType<jsonObject>> newNotes;

							userObject->data.push_back({ "type"s, "item"s });

							for (const auto& j : notes)
							{
								string data = json::utility::fromUTF8JSON(get<string>(j->data.back().second), utility::getCodepage());

								json::utility::appendArray(move(data), newNotes);
							}

							userObject->data.push_back({ "notes"s, move(newNotes) });

							newObject->data.push_back({ itemName, move(userObject) });
						}

						updateBuilder.append(i->first, move(newObject));
					}
				}
			}

			ofstream(pathToProjectFile) << updateBuilder;
		}
		catch (const runtime_error& e)
		{
			success = false;

			message = e.what();
		}

		builder.
			append("success", success).
			append("message", move(message));

		return builder;
	}
}
