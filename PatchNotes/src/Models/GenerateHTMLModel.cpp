#include "GenerateHTMLModel.h"

#include "PatchNotesUtility.h"
#include "PatchNotesConstants.h"
#include "HTMLAdapter.h"

using namespace std;

namespace models
{
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
		string message = format(R"(Файл "{}.html" успешно сгенерирован)", projectFileName);

		pathToProjectFile.append(globals::dataFolder).append(projectFileName) += ".json";

		ifstream(pathToProjectFile) >> projectFile;

		(out /= fromUTF8JSON(gui_framework::GUIFramework::get().getJSONSettings().getString("pathToProject"), utility::getCodepage())).append(patch_notes_constants::htmlGeneratedFolder);

		filesystem::create_directory(out);

		ofstream(out / (projectFileName + ".html")) << HTMLAdapter(projectFile, mainWindow).getHTML();

		this->updateIndex(out, projectFileName);

		builder.
			append("success", success).
			append("message", move(message));

		return builder;
	}

	void GenerateHTMLModel::updateIndex(const filesystem::path& outFolder, const string& projectFileName)
	{
		ostringstream indexHTMLData;
		ifstream indexHTML(outFolder / "index.html");
		string tem;
		bool alreadyAdded = false;

		while (getline(indexHTML, tem))
		{
			if (tem.find(projectFileName) != string::npos)
			{
				return;
			}
			else if (tem.find("</body>") != string::npos)
			{
				indexHTMLData << "\t<div>" << endl <<
					format(R"({0}<a href="{1}.html">{1}</a>)", "\t\t", projectFileName) << endl <<
					"\t</div>" << endl << endl;
			}

			indexHTMLData << tem << endl;
		}

		ofstream(outFolder / "index.html") << indexHTMLData.view();
	}

	GenerateHTMLModel::GenerateHTMLModel(gui_framework::BaseComposite* mainWindow) :
		mainWindow(mainWindow)
	{

	}
}
