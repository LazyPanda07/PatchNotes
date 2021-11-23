#include "GenerateHTMLModel.h"

#include "Initializer.h"
#include "PatchNotesUtility.h"
#include "PatchNotesConstants.h"
#include "HTMLAdapter.h"

#pragma warning(disable: 6031)
#pragma warning(disable: 4834)

using namespace std;

string makeTableRows(const vector<string>& data, size_t index, size_t columns);

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
	<link rel="shortcut icon" href="{}" type="image/x-icon">
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
)", projectName, logo ? *logo : Initializer::get().getFavicon(), logo ? *logo : "", logo ? "" : "hidden") << endl;
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

		bool isBackgroundImageLoaded = Initializer::get().getIsBackgroundImageLoaded();
		bool isFaviconLoaded = Initializer::get().getIsFaviconLoaded();

		if (isBackgroundImageLoaded && isFaviconLoaded)
		{
			filesystem::create_directory(out);

			ofstream(out / (projectFileName + ".html")) << HTMLAdapter(projectFile, mainWindow).getHTML();
			ofstream(out / patch_notes_constants::stylesFileName) << patch_notes_constants::styles;

			this->updateIndex(out, projectFileName);

			success = true;
			message = format("Файл \"{}.html\" успешно сгенерирован", projectFileName);
		}
		else if (!isBackgroundImageLoaded)
		{
			success = false;
			message = format("Не удалось сгенерировать изменения.\nЕще не завершена загрузка заднего фона.\nПовторите команду позже.");
		}
		else if (!isFaviconLoaded)
		{
			success = false;
			message = format("Не удалось сгенерировать изменения.\nЕще не завершена загрузка favicon.\nПовторите команду позже.");
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
		static constexpr string_view table = "<table style=\"width: 100%;\">\n";
		vector<string> rowsData = { GenerateHTMLModel::generatePatchLink(projectFileName) };
		
		if (!indexHTML.is_open())
		{
			GenerateHTMLModel::generateIndexHTML(outFolder, projectFileName.substr(0, projectFileName.rfind('_')));

			indexHTML.open(pathToIndexHTML);
		}

		indexHTMLData.reserve(filesystem::file_size(pathToIndexHTML));

		string tem;

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
				rowsData.push_back(move(tem) + '\n');

				continue;
			}

			indexHTMLData += tem + '\n';
		}

		while (rowsData.size() < 5)
		{
			rowsData.push_back(GenerateHTMLModel::generateEmptyPatchLink());
		}

		indexHTMLData.insert(indexHTMLData.find(table) + table.size(), makeTableRows(rowsData, 0, 5));
		
		ofstream(pathToIndexHTML) << indexHTMLData;
	}

	GenerateHTMLModel::GenerateHTMLModel(gui_framework::BaseComposite* mainWindow) :
		mainWindow(mainWindow)
	{

	}
}

string makeTableRows(const vector<string>& data, size_t index, size_t columns)
{
	try
	{
		data.at(index);
	}
	catch (const exception&)
	{
		return ""s;
	}

	string tem = "\t\t\t<tr>\n";
	size_t current = 0;

	while (current != columns)
	{
		if (data.size() == index + current)
		{
			break;
		}

		tem += data[index + current++];
	}

	tem += "\t\t\t</tr>\n";

	return tem + makeTableRows(data, index + current, columns);
}
