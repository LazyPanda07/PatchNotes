#include "CategoryModel.h"

#include "PatchNotesUtility.h"
#include "PatchNotesConstants.h"
#include "Exceptions/CantFindValueException.h"

using namespace std;

namespace models
{
	json::JSONBuilder CategoryModel::processData(const json::JSONParser& data)
	{
		using json::utility::objectSmartPointer;
		using json::utility::jsonObject;
		using json::utility::toUTF8JSON;
		using json::utility::fromUTF8JSON;

		uint32_t codepage = utility::getCodepage();
		json::JSONBuilder builder(codepage);
		json::JSONBuilder updateBuilder(CP_UTF8);
		string projectFile = fromUTF8JSON(data.getString("projectFile"), codepage);
		string categoryName = fromUTF8JSON(data.getString("category"), codepage);
		bool success = true;
		string message = format(localization::TextLocalization::get()[patch_notes_localization::categoryAddedSuccessfully], categoryName);
		filesystem::path pathToProjectFile;
		const string& utf8CategoryName = data.getString("category");

		pathToProjectFile.append(globals::dataFolder).append(projectFile) += ".json";

		updateBuilder.
			append("projectName"s, toUTF8JSON(projectFile.substr(0, projectFile.rfind('_')), codepage)).
			append("projectVersion"s, toUTF8JSON(projectFile.substr(projectFile.rfind('_') + 1), codepage));

		try
		{
			utility::copyJSON(pathToProjectFile, updateBuilder);

			const json::JSONBuilder& checkCategory = updateBuilder;

			try
			{
				checkCategory[categoryName];

				throw runtime_error(format(localization::TextLocalization::get()[patch_notes_localization::categoryAlreadyExists], categoryName));
			}
			catch (const json::exceptions::CantFindValueException&)
			{

			}

			objectSmartPointer<jsonObject> category = json::utility::make_object<jsonObject>();

			category->data.push_back({ "type"s, "category"s });

			updateBuilder.append(utf8CategoryName, move(category));

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
