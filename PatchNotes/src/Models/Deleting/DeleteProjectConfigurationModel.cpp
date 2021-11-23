#include "DeleteProjectConfigurationModel.h"

#include <filesystem>

#include "headers.h"
#include "PatchNotesUtility.h"
#include "PatchNotesConstants.h"

using namespace std;

namespace models
{
	json::JSONBuilder DeleteProjectConfigurationModel::processData(const json::JSONParser& data)
	{
		filesystem::path projectToDelete = data.getString("projectToDelete");
		string message;
		bool success = filesystem::remove(projectToDelete);
		localization::TextLocalization& textLocalization = localization::TextLocalization::get();

		if (success)
		{
			message = format(textLocalization[patch_notes_localization::configurationSuccessfullyDeleted], projectToDelete.filename().stem().string());
		}
		else
		{
			message = format(textLocalization[patch_notes_localization::failedToDeleteConfiguration], projectToDelete.filename().stem().string());
		}

		return json::JSONBuilder(CP_UTF8).
			append("success", success).
			append("message", move(message));
	}
}
