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
		string projectFileName = fromUTF8JSON(data.get<string>("projectFile"), codepage);
		filesystem::path pathToProjectFile;
		filesystem::path out;
		json::JSONParser projectFile;
		bool success = true;
		string message = format(R"(Файл "{}.html" успешно сгенерирован)", projectFileName);

		pathToProjectFile.append(dataFolder).append(projectFileName) += ".json";

		ifstream(pathToProjectFile) >> projectFile;

		(out /= filesystem::current_path()).append("out");

		filesystem::create_directory(out);

		out /= projectFileName + ".html";

		ofstream(out) << HTMLAdapter(projectFile, mainWindow).getHTML();

		builder.
			append("success", success).
			append("message", move(message));

		return builder;
	}

	GenerateHTMLModel::GenerateHTMLModel(gui_framework::BaseComposite* mainWindow) :
		mainWindow(mainWindow)
	{

	}
}
