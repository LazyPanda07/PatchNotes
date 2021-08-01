#include "CategoryConfigurationModel.h"

#include "PatchNotesUtility.h"
#include "PatchNotesConstants.h"

using namespace std;

namespace models
{
	json::JSONBuilder CategoryConfigurationModel::processData(const json::JSONParser& data)
	{
		using json::utility::objectSmartPointer;
		using json::utility::jsonObject;
		using json::utility::toUTF8JSON;

		uint32_t codepage = utility::getCodepage();
		json::JSONBuilder builder(CP_UTF8);
		const string& projectFile = data.get<string>("projectFile");
		const string& categoryName = data.get<string>("category");
		bool success = true;
		string message = toUTF8JSON(R"(Категория ")", codepage) + categoryName + toUTF8JSON(R"(" успешно добавлена)", codepage);
		json::JSONBuilder updateBuilder(CP_UTF8);
		filesystem::path pathToProjectFile;

		pathToProjectFile.append(dataFolder).append(projectFile) += ".json";

		updateBuilder.
			append("projectName"s, projectFile.substr(0, projectFile.rfind('_'))).
			append("projectVersion"s, projectFile.substr(projectFile.rfind('_') + 1));

		try
		{
			utility::copyJSON(pathToProjectFile, updateBuilder);

			if (updateBuilder.contains(categoryName, json::utility::variantTypeEnum::jJSONObject))
			{
				throw runtime_error(toUTF8JSON("Категория с таким названием уже существует", codepage));
			}

			objectSmartPointer<jsonObject> category = json::utility::make_object<jsonObject>();

			category->data.push_back({ "type"s, "category"s });

			updateBuilder.append(categoryName, move(category));

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
