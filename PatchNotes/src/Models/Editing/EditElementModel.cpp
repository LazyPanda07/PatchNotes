#include "EditElementModel.h"

#include "PatchNotesUtility.h"
#include "PatchNotesConstants.h"

using namespace std;

namespace models
{
	json::JSONBuilder EditElementModel::processData(const json::JSONParser& data)
	{
		uint32_t codepage = utility::getCodepage();
		json::JSONBuilder builder(codepage);
		const string& category = data.getString("category");
		const string& element = data.getString("element");
		const string& newElement = data.getString("newElement");
		filesystem::path pathToProject = filesystem::path(globals::dataFolder) /= data.getString("project") + ".json";
		json::JSONParser projectConfiguration = ifstream(pathToProject);
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
						j.first = newElement;

						break;
					}
				}

				break;
			}
		}

		ofstream(pathToProject) << projectConfiguration;

		message = format(R"(Ёлемент \"{}\" изменен на \"{}\")", json::utility::fromUTF8JSON(element, codepage), json::utility::fromUTF8JSON(newElement, codepage));

		builder.
			append("success", success).
			append("message", move(message));

		return builder;
	}
}
