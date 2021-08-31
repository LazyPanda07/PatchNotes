#include "HTMLAdapter.h"

#include <format>

#include "Components/ProgressBars/ProgressBar.h"

using namespace std;

void HTMLAdapter::addPageInformation(const string& projectName, const string& version)
{
	html += format(R"(<!DOCTYPE html>

<head>
    <meta charset="UTF-8">
    <meta http-equiv="X-UA-Compatible" content="IE=edge">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>{} {}</title>
</head>

<body>

)", projectName, version);
}

void HTMLAdapter::addProjectNameAndVersion(const string& projectName, const string& version)
{
	this->addPageInformation(projectName, version);

	html += format("\t<h1>{} {}</h1>\n\n", projectName, version);
}

void HTMLAdapter::addCategory(const string& category)
{
	html += format("\t<h2>{}</h2>\n\n", category);
}

void HTMLAdapter::addItem(const string& item, const vector<string>& notes)
{
	html += format("\t<h4>{}</h4>\n\n", item);

	for (const auto& i : notes)
	{
		html += format("\t<div>&#8226; {}</div><br>\n\n", i);
	}

	html += "\t<br>\n\n";
}

void HTMLAdapter::addFooterInformation(const string& information)
{
	html += format(R"({}
</body>

</html>
)", information);
}

HTMLAdapter::HTMLAdapter(const json::JSONParser& jsonSchema, gui_framework::BaseComposite* mainWindow)
{
	using namespace json;
	using namespace json::utility;

	int size = 0;
	gui_framework::ProgressBar* updateProgressBar = static_cast<gui_framework::ProgressBar*>(static_cast<gui_framework::BaseComposite*>(mainWindow->findChild(L"PatchNotesUI"))->findChild(L"GenerateHTMLProgressBar"));

	this->addProjectNameAndVersion(jsonSchema.getString("projectName"), jsonSchema.getString("projectVersion"));

	for (const auto& i : jsonSchema)
	{
		size++;
	}

	updateProgressBar->setMaxRange(size * 10);

	for (const auto& i : jsonSchema)
	{
		if (i->second.index() == static_cast<size_t>(variantTypeEnum::jJSONObject))
		{
			const objectSmartPointer<jsonObject>& category = get<static_cast<size_t>(variantTypeEnum::jJSONObject)>(i->second);
			const string& type = get<string>(find_if(category->data.begin(), category->data.end(), [](const pair<string, jsonObject::variantType>& value) { return value.first == "type"; })->second);

			this->addCategory(i->first);

			for (const auto& j : category->data)
			{
				if (j.second.index() == static_cast<size_t>(variantTypeEnum::jJSONObject))
				{
					const objectSmartPointer<jsonObject>& item = get<static_cast<size_t>(variantTypeEnum::jJSONObject)>(j.second);
					const vector<objectSmartPointer<jsonObject>>& data = get<vector<objectSmartPointer<jsonObject>>>(find_if(item->data.begin(), item->data.end(), [](const pair<string, jsonObject::variantType>& value) { return value.first == "notes"; })->second);
					vector<string> notes;

					for (const auto& k : data)
					{
						notes.push_back(get<string>(k->data.back().second));
					}

					this->addItem(j.first, notes);
				}
			}
		}

		updateProgressBar->update();
	}

	this->addFooterInformation();
}

string& HTMLAdapter::getHTML()
{
	return html;
}
