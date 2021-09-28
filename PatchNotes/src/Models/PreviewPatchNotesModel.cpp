#include "PreviewPatchNotesModel.h"

#include "Initializer.h"
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
		string absolutePathToFile = filesystem::absolute(out).string();
		bool success;
		string message;

		pathToProjectFile.append(globals::dataFolder).append(projectFileName) += ".json";

		ifstream(pathToProjectFile) >> projectFile;

		bool isBackgroundImageLoaded = Initializer::get().getIsBackgroundImageLoaded();
		bool isFaviconLoaded = Initializer::get().getIsFaviconLoaded();

		if (isBackgroundImageLoaded && isFaviconLoaded)
		{
			ofstream(out) << HTMLAdapter(projectFile, mainWindow).getHTML();
			ofstream(filesystem::temp_directory_path() / patch_notes_constants::stylesFileName) << patch_notes_constants::styles;

			success = true;
			message = "Данные для предпросмотра успешно сгенерированы";
		}
		else if (!isBackgroundImageLoaded)
		{
			success = false;
			message = format("Не удалось сгенерировать данные для предпросмотра.\nЕще не завершена загрузка заднего фона.\nПовторите команду позже.");
		}
		else if (!isFaviconLoaded)
		{
			success = false;
			message = format("Не удалось сгенерировать данные для предпросмотра.\nЕще не завершена загрузка favicon.\nПовторите команду позже.");
		}

		ranges::replace(absolutePathToFile, '\\', '/');

		builder.
			append("success", success).
			append("message", move(message)).
			append("pathToFile", move(absolutePathToFile));

		return builder;
	}

	PreviewPatchNotesModel::PreviewPatchNotesModel(gui_framework::BaseComposite* mainWindow) :
		mainWindow(mainWindow)
	{
		
	}
}
