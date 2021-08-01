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

		uint32_t codepage = utility::getCodepage();
		json::JSONBuilder builder(CP_UTF8);
		const string& projectFileName = data.get<string>("projectFile");
		filesystem::path pathToProjectFile;
		filesystem::path out;
		json::JSONParser projectFile;
		bool success = true;
		string message = toUTF8JSON(R"(Файл ")", codepage) + projectFileName + toUTF8JSON(R"(.html" успешно сгенерирован)", codepage);

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
