#include "PreviewPatchNotesModel.h"

#include "PatchNotesUtility.h"
#include "PatchNotesConstants.h"
#include "HTMLAdapter.h"

using namespace std;

namespace models
{
	json::JSONBuilder PreviewPatchNotesModel::processData(const json::JSONParser& data)
	{
		using json::utility::toUTF8JSON;
		using json::utility::fromUTF8JSON;

		uint32_t codepage = utility::getCodepage();
		json::JSONBuilder builder(codepage);
		string projectFileName = fromUTF8JSON(data.getString("projectFile"), codepage);
		filesystem::path pathToProjectFile;
		filesystem::path out = filesystem::temp_directory_path() / (projectFileName + ".html");
		json::JSONParser projectFile;
		bool success = true;
		string absolutePathToFile = filesystem::absolute(out).string();

		pathToProjectFile.append(globals::dataFolder).append(projectFileName) += ".json";

		ifstream(pathToProjectFile) >> projectFile;

		ofstream(out) << HTMLAdapter(projectFile, mainWindow).getHTML();

		ranges::replace(absolutePathToFile, '\\', '/');

		builder.
			append("success", success).
			append("pathToFile", move(absolutePathToFile));

		return builder;
	}

	PreviewPatchNotesModel::PreviewPatchNotesModel(gui_framework::BaseComposite* mainWindow) :
		mainWindow(mainWindow)
	{
		
	}
}
