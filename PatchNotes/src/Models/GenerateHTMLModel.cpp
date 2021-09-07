#include "GenerateHTMLModel.h"

#include "Initializer.h"
#include "PatchNotesUtility.h"
#include "PatchNotesConstants.h"
#include "HTMLAdapter.h"

using namespace std;

namespace models
{
	void GenerateHTMLModel::generateIndexHTML(const filesystem::path& outFolder, const string& projectName)
	{
		ofstream indexHTML(outFolder / "index.html");
		gui_framework::GUIFramework& instance = gui_framework::GUIFramework::get();
		const string* logo = nullptr;

		try
		{
			logo = instance.getJSONSettings().getNull("pathToProjectLogo");
		}
		catch (const bad_variant_access&)
		{
			logo = &instance.getJSONSettings().getString("pathToProjectLogo");
		}

		indexHTML << format(R"(<!DOCTYPE html>
<html>

<head>
    <meta charset="UTF-8">
    <meta http-equiv="X-UA-Compatible" content="IE=edge">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>{}</title>
    <link href="styles.css" rel="stylesheet" type="text/css" />
</head>

<body>

    <div class="title-container">
		<img src="{}" alt="Project logo" class="project-logo" {}>
        <div class="title">Patch notes</div>
    </div>

    <div class="links-container">
        <table style="width: 100%;">
        </table>
    </div>

</body>

</html>
)", projectName, logo ? *logo : "", logo ? "" : "hidden") << endl;
	}

	string GenerateHTMLModel::generatePatchLink(const string& projectName)
	{
		return format(R"({0}<td><a href="{1}.html" class="link-to-patch">{1}</a></td>{2})", "\t\t\t\t", projectName, '\n');
	}

	string GenerateHTMLModel::generateEmptyPatchLink()
	{
		return "\t\t\t\t<td></td>\n";
	}

	json::JSONBuilder GenerateHTMLModel::processData(const json::JSONParser& data)
	{
		using json::utility::toUTF8JSON;
		using json::utility::fromUTF8JSON;

		uint32_t codepage = utility::getCodepage();
		json::JSONBuilder builder(codepage);
		string projectFileName = fromUTF8JSON(data.getString("projectFile"), codepage);
		filesystem::path pathToProjectFile;
		filesystem::path out;
		json::JSONParser projectFile;
		bool success;
		string message;

		pathToProjectFile.append(globals::dataFolder).append(projectFileName) += ".json";

		ifstream(pathToProjectFile) >> projectFile;

		(out /= fromUTF8JSON(gui_framework::GUIFramework::get().getJSONSettings().getString("pathToProject"), utility::getCodepage())).append(patch_notes_constants::htmlGeneratedFolder);

		if (Initializer::get().getIsBackgroundImageLoaded())
		{
			filesystem::create_directory(out);

			ofstream(out / (projectFileName + ".html")) << HTMLAdapter(projectFile, mainWindow).getHTML();
			ofstream(out / patch_notes_constants::stylesFileName) << patch_notes_constants::styles;

			this->updateIndex(out, projectFileName);

			success = true;
			message = format("Файл \"{}.html\" успешно сгенерирован", projectFileName);
		}
		else
		{
			success = false;
			message = format("Не удалось сгенерировать изменения.\nЕще не завершена загрузка заднего фона.\nПовторите команду позже.");
		}

		builder.
			append("success", success).
			append("message", move(message));

		return builder;
	}

	void GenerateHTMLModel::updateIndex(const filesystem::path& outFolder, const string& projectFileName)
	{
		string indexHTMLData;
		filesystem::path pathToIndexHTML = outFolder / "index.html";
		ifstream indexHTML(pathToIndexHTML);
		string tem;
		static constexpr string_view openTable = "<table";
		vector<string> result = { GenerateHTMLModel::generatePatchLink(projectFileName) };
		size_t start = 0;

		if (!indexHTML.is_open())
		{
			GenerateHTMLModel::generateIndexHTML(outFolder, projectFileName.substr(0, projectFileName.rfind('_')));

			indexHTML.open(pathToIndexHTML);
		}

		indexHTMLData.reserve(filesystem::file_size(pathToIndexHTML));

		while (getline(indexHTML, tem))
		{
			if (tem.find(projectFileName) != string::npos)
			{
				return;
			}
			else if (tem.find("<td></td>") != string::npos || tem.find("<tr>") != string::npos || tem.find("</tr>") != string::npos)
			{
				continue;
			}
			else if (tem.find("<td>") != string::npos)
			{
				result.push_back(move(tem) + '\n');
				
				continue;
			}

			indexHTMLData += tem + '\n';
		}

		while (result.size() < 5)
		{
			result.push_back(GenerateHTMLModel::generateEmptyPatchLink());
		}

		start = indexHTMLData.find(">", indexHTMLData.find(openTable)) + 1;

		for (size_t i = 0; i < result.size(); i++)
		{
			if (!i)
			{
				indexHTMLData.insert(start, "\n\t\t\t<tr>");

				start += 9;
			}
			else if (!(i % 5))
			{
				indexHTMLData.insert(start, "\t\t\t</tr>\n");

				start += 10;
			}

			indexHTMLData.insert(start, result[i]);

			start += result[i].size();
		}

		indexHTMLData.insert(start, "\t\t\t</tr>\n");

		ofstream(pathToIndexHTML) << indexHTMLData;
	}

	GenerateHTMLModel::GenerateHTMLModel(gui_framework::BaseComposite* mainWindow) :
		mainWindow(mainWindow)
	{

	}
}
