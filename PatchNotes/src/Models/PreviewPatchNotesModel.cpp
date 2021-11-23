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

		json::JSONBuilder builder(CP_UTF8);
		string projectFileName = data.getString("projectFile");
		filesystem::path pathToProjectFile;
		filesystem::path out = filesystem::temp_directory_path() / (projectFileName + ".html");
		json::JSONParser projectFile;
		string absolutePathToFile = filesystem::absolute(out).string();
		bool success;
		string message;
		localization::TextLocalization& textLocalization = localization::TextLocalization::get();

		pathToProjectFile.append(globals::dataFolder).append(projectFileName) += ".json";

		ifstream(pathToProjectFile) >> projectFile;

		bool isBackgroundImageLoaded = Initializer::get().getIsBackgroundImageLoaded();
		bool isFaviconLoaded = Initializer::get().getIsFaviconLoaded();

		if (isBackgroundImageLoaded && isFaviconLoaded)
		{
			ofstream(out) << HTMLAdapter(projectFile, mainWindow).getHTML();
			ofstream(filesystem::temp_directory_path() / patch_notes_constants::stylesFileName) << patch_notes_constants::styles;

			success = true;
			message = textLocalization[patch_notes_localization::dataForPreviewSuccessfullyGenerated];
		}
		else if (!isBackgroundImageLoaded)
		{
			success = false;
			message = textLocalization[patch_notes_localization::failedToGeneratePreview] + '\n' +
				textLocalization[patch_notes_localization::backgroundNotLoadedYet] + '\n' +
				textLocalization[patch_notes_localization::repeatCommandLater];
				
		}
		else if (!isFaviconLoaded)
		{
			success = false;
			message = textLocalization[patch_notes_localization::failedToGeneratePreview] + '\n' +
				textLocalization[patch_notes_localization::faviconNotLoadedYet] + '\n' +
				textLocalization[patch_notes_localization::repeatCommandLater];
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
