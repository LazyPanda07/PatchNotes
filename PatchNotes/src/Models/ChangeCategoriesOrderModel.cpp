#include "ChangeCategoriesOrderModel.h"

#include "JSONArrayWrapper.h"
#include "Utility/Utility.h"

#include "PatchNotesConstants.h"
#include "PatchNotesUtility.h"

using namespace std;

namespace models
{
	json::JSONBuilder ChangeCategoriesOrderModel::processData(const json::JSONParser& data)
	{
		using json::utility::objectSmartPointer;
		using json::utility::jsonObject;

		uint32_t codepage = utility::getCodepage();
		json::JSONBuilder builder(codepage);
		filesystem::path pathToProjectConfiguration = filesystem::path(globals::dataFolder) /= data.getString("project") + ".json";
		vector<string> temCategories = json::utility::JSONArrayWrapper(data.getArray("categories")).getAsStringArray();
		vector<wstring> categories;
		unordered_map<wstring, objectSmartPointer<jsonObject>*> mappedCategories;
		json::JSONParser projectConfiguration = ifstream(pathToProjectConfiguration);
		json::JSONBuilder outputData(CP_UTF8);

		for (const auto& i : projectConfiguration)
		{
			if (i->second.index() == static_cast<size_t>(json::utility::variantTypeEnum::jJSONObject))
			{
				mappedCategories[gui_framework::utility::to_wstring(i->first, CP_UTF8)] = const_cast<objectSmartPointer<jsonObject>*>(&get<objectSmartPointer<jsonObject>>(i->second));
			}
			else
			{
				outputData[i->first] = get<string>(i->second);
			}
		}

		categories.reserve(temCategories.size());

		ranges::for_each(temCategories, [&categories](const string& category) { categories.push_back(gui_framework::utility::to_wstring(category, CP_UTF8)); });

		for (size_t i = 0; i < categories.size(); i++)
		{
			auto it = mappedCategories.find(categories[i]);

			if (it != mappedCategories.end())
			{
				outputData.appendObject(gui_framework::utility::to_string(it->first, CP_UTF8), move(*it->second));

				mappedCategories.erase(it);
			}
		}

		for (const auto& i : mappedCategories)
		{
			outputData.appendObject(gui_framework::utility::to_string(i.first, CP_UTF8), move(*i.second));
		}

		ofstream(pathToProjectConfiguration) << outputData;

		builder.
			append("success", true).
			append("message", "Порядок категорий успешно изменен"s);

		return builder;
	}
}
