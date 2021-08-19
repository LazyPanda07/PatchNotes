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
		using json::utility::toUTF8JSON;

		uint32_t codepage = utility::getCodepage();
		json::JSONBuilder updateBuilder(CP_UTF8);
		json::JSONBuilder builder(CP_UTF8);
		filesystem::path pathToProjectFile;
		const string& itemName = data.get<string>("item");
		const string& categoryName =  data.get<string>("category");
		const vector<objectSmartPointer<jsonObject>>& notes = data.get<vector<objectSmartPointer<jsonObject>>>("notes");
		bool success = true;
		string message = toUTF8JSON(R"(Ёлемент \")", codepage) + itemName + toUTF8JSON(R"(\" успешно добавлен)", codepage);
		const string& projectNameAndVersion = data.get<string>("projectFile");

		pathToProjectFile.append(globals::dataFolder).append(json::utility::fromUTF8JSON(projectNameAndVersion, codepage)) += ".json";

		updateBuilder.
			append("projectName"s, projectNameAndVersion.substr(0, projectNameAndVersion.rfind('_'))).
			append("projectVersion"s, projectNameAndVersion.substr(projectNameAndVersion.rfind('_') + 1));

		try
		{
			utility::copyJSON(pathToProjectFile, updateBuilder);

			if (updateBuilder.contains(itemName, json::utility::variantTypeEnum::jJSONObject))
			{
				throw runtime_error(toUTF8JSON(R"(Ёлемент \")", codepage) + itemName + toUTF8JSON(R"(\" уже существует)", codepage));
			}

			objectSmartPointer<jsonObject> userObject = json::utility::make_object<jsonObject>();
			vector<smartPointerType<jsonObject>> newNotes;

			userObject->data.push_back({ "type"s, "item"s });

			for (const auto& j : notes)
			{
				json::utility::appendArray(get<string>(j->data.back().second), newNotes);
			}

			userObject->data.push_back({ "notes"s, move(newNotes) });

			get<objectSmartPointer<jsonObject>>(updateBuilder[categoryName])->data.push_back({ itemName, move(userObject) });

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
