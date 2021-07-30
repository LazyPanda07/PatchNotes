#include "GenerateHTMLModel.h"

#include "PatchNotesUtility.h"
#include "PatchNotesConstants.h"
#include "HTMLAdapter.h"

using namespace std;

namespace models
{
	json::JSONBuilder GenerateHTMLModel::processData(const json::JSONParser& data)
	{
		json::JSONBuilder builder(utility::getCodepage());
		const string& projectFileName = data.get<string>("projectFile");
		filesystem::path pathToProjectFile;
		filesystem::path out;
		json::JSONParser projectFile;
		bool success = true;
		string message = format(R"(Файл "{}" успешно сгенерирован)", projectFileName + ".html");

		pathToProjectFile.append(dataFolder).append(projectFileName) += ".json";

		ifstream(pathToProjectFile) >> projectFile;

		(out /= filesystem::current_path()).append("out");

		filesystem::create_directory(out);

		out /= projectFileName + ".html";

		ofstream(out) << HTMLAdapter(projectFile, updateProgressBar).getHTML();

		builder.
			append("success", success).
			append("message", move(message));

		return builder;
	}

	GenerateHTMLModel::GenerateHTMLModel(gui_framework::ProgressBar* updateProgressBar) :
		updateProgressBar(updateProgressBar)
	{

	}
}
