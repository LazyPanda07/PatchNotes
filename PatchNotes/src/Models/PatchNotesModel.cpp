#include "PatchNotesModel.h"

#include "headers.h"

#include "PatchNotesUtility.h"
#include "PatchNotesConstants.h"

using namespace std;

namespace models
{
	json::JSONBuilder PatchNotesModel::processData(const json::JSONParser& data)
	{
		using json::utility::jsonObject;
		using json::utility::toUTF8JSON;

		json::JSONBuilder updateBuilder(CP_UTF8);
		json::JSONBuilder builder(CP_UTF8);
		filesystem::path pathToProjectFile;
		const string& itemName = data.getString("item");
		const string& categoryName =  data.getString("category");
		const vector<jsonObject>& notes = data.get<vector<jsonObject>>("notes");
		bool success = true;
		localization::TextLocalization& textLocalization = localization::TextLocalization::get();
		string message = format(textLocalization[patch_notes_localization::elementSuccessfullyAdded], itemName);
		const string& projectNameAndVersion = data.getString("projectFile");

		pathToProjectFile.append(globals::dataFolder).append(projectNameAndVersion) += ".json";

		updateBuilder.
			append("projectName"s, projectNameAndVersion.substr(0, projectNameAndVersion.rfind('_'))).
			append("projectVersion"s, projectNameAndVersion.substr(projectNameAndVersion.rfind('_') + 1));

		try
		{
			utility::copyJSON(pathToProjectFile, updateBuilder);

			const json::JSONBuilder& checkItem = updateBuilder;

			try
			{
				if (get<jsonObject>(checkItem[categoryName]).contains(itemName, json::utility::variantTypeEnum::jJSONObject))
				{
					throw runtime_error(format(textLocalization[patch_notes_localization::elementAlreadyExists], itemName));
				}
			}
			catch (const json::exceptions::CantFindValueException&)
			{

			}

			jsonObject userObject;
			vector<jsonObject> newNotes;

			userObject.data.push_back({ "type"s, "item"s });

			for (const auto& j : notes)
			{
				json::utility::appendArray(get<string>(j.data.back().second), newNotes);
			}

			userObject.data.push_back({ "notes"s, move(newNotes) });

			get<jsonObject>(updateBuilder[categoryName]).data.push_back({ itemName, move(userObject) });

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
