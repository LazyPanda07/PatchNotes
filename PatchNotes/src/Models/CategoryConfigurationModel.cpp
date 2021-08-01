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
		using json::utility::fromUTF8JSON;

		uint32_t codepage = utility::getCodepage();
		json::JSONBuilder builder(codepage);
		json::JSONBuilder updateBuilder(CP_UTF8);
		string projectFile = fromUTF8JSON(data.get<string>("projectFile"), codepage);
		string categoryName = fromUTF8JSON(data.get<string>("category"), codepage);
		bool success = true;
		string message = format(R"(Категория \"{}\" успешно добавлена)", categoryName);
		filesystem::path pathToProjectFile;
		const string& utf8CategoryName = data.get<string>("category");

		pathToProjectFile.append(dataFolder).append(projectFile) += ".json";

		updateBuilder.
			append("projectName"s, toUTF8JSON(projectFile.substr(0, projectFile.rfind('_')), codepage)).
			append("projectVersion"s, toUTF8JSON(projectFile.substr(projectFile.rfind('_') + 1), codepage));

		try
		{
			utility::copyJSON(pathToProjectFile, updateBuilder);

			if (updateBuilder.contains(utf8CategoryName, json::utility::variantTypeEnum::jJSONObject))
			{
				throw runtime_error(format(R"(Категория \"{}\" уже существует)", categoryName));
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
