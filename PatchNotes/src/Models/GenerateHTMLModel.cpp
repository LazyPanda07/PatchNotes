#include "GenerateHTMLModel.h"

#include "PatchNotesUtility.h"
#include "PatchNotesConstants.h"
#include "HTMLAdapter.h"

using namespace std;

namespace models
{
	void GenerateHTMLModel::generateIndexHTML(const filesystem::path& outFolder, const string& projectName)
	{
		ofstream indexHTML(outFolder / "index.html");

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
        <div class="title">Patch notes</div>
    </div>

    <div class="links-container">
        <table style="width:100%;">
        </table>
    </div>

</body>

</html>
)", projectName) << endl;
	}

	string GenerateHTMLModel::insertPatchLink(const string& projectName)
	{
		return format(R"({0}{1}<td>{0}{2}<a href="{3}.html" class="link-to-patch">{3}</a>{0}{1}</td>)", '\n', "\t\t\t\t", "\t\t\t\t\t", projectName);
	}

	string GenerateHTMLModel::insertPatchRowAndLink(const string& projectName)
	{
		string result = "\n\t\t\t<tr>";

		result += GenerateHTMLModel::insertPatchLink(projectName);

		result += "\n\t\t\t</tr>";

		return result;
	}

	string GenerateHTMLModel::insertEmptyPatchLink()
	{
		return "\n<td></td>";
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
		bool success = true;
		string message = format("Файл \"{}.html\" успешно сгенерирован", projectFileName);

		pathToProjectFile.append(globals::dataFolder).append(projectFileName) += ".json";

		ifstream(pathToProjectFile) >> projectFile;

		(out /= fromUTF8JSON(gui_framework::GUIFramework::get().getJSONSettings().getString("pathToProject"), utility::getCodepage())).append(patch_notes_constants::htmlGeneratedFolder);

		filesystem::create_directory(out);

		ofstream(out / (projectFileName + ".html")) << HTMLAdapter(projectFile, mainWindow).getHTML();
		ofstream(out / patch_notes_constants::stylesFileName) << patch_notes_constants::styles;

		this->updateIndex(out, projectFileName);

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
		size_t columnCount = 0;
		static constexpr string_view closeTd = "</td>";
		static constexpr string_view closeTr = "</tr>";
		static constexpr string_view openTable = "<table";

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
			else if (tem.find("<td></td>") != string::npos)
			{
				continue;
			}
			else if (tem.find("<td>") != string::npos)
			{
				columnCount++;
			}

			indexHTMLData += tem + '\n';
		}

		if (columnCount % 5)
		{
			indexHTMLData.insert(indexHTMLData.rfind(closeTd) + closeTd.size(), GenerateHTMLModel::insertPatchLink(projectFileName));
		}
		else
		{
			size_t insertRowPosition = 0;

			if (indexHTMLData.find("</tr>") != string::npos)
			{
				insertRowPosition = indexHTMLData.rfind(closeTr) + closeTr.size();
			}
			else
			{
				insertRowPosition = indexHTMLData.find('\n', indexHTMLData.find("<table"));
			}

			indexHTMLData.insert(insertRowPosition, GenerateHTMLModel::insertPatchRowAndLink(projectFileName));
		}

		while (columnCount < 4)
		{
			indexHTMLData.insert(indexHTMLData.rfind(closeTd) + closeTd.size(), GenerateHTMLModel::insertEmptyPatchLink());

			columnCount++;
		}

		ofstream(pathToIndexHTML) << indexHTMLData;
	}

	GenerateHTMLModel::GenerateHTMLModel(gui_framework::BaseComposite* mainWindow) :
		mainWindow(mainWindow)
	{

	}
}
