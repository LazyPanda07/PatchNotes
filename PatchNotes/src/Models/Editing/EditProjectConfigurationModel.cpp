#include "EditProjectConfigurationModel.h"

#include "PatchNotesUtility.h"
#include "PatchNotesConstants.h"

using namespace std;

namespace models
{
    json::JSONBuilder EditProjectConfigurationModel::processData(const json::JSONParser& data)
    {
        json::JSONBuilder builder(CP_UTF8);
        const string& projectToEdit = data.getString("projectToEdit");
        filesystem::path pathToProject = filesystem::path(globals::dataFolder) /= projectToEdit + ".json";
        const string& newProjectName = data.getString("newProjectName");
        const string& newProjectVersion =  data.getString("newProjectVersion");
        filesystem::path newProject = filesystem::path(globals::dataFolder);
        bool success = true;
        string message;

        if (newProjectName.size())
        {
            newProject /= newProjectName;
        }
        else
        {
            newProject /= projectToEdit.substr(0, projectToEdit.rfind('_'));
        }
        
        if (newProjectVersion.size())
        {
            newProject += '_' + newProjectVersion;
        }
        else
        {
            newProject += projectToEdit.substr(projectToEdit.rfind('_'));
        }

        newProject += ".json";

        filesystem::rename(pathToProject, newProject);

        message = format(localization::TextLocalization::get()[patch_notes_localization::configurationChanged], projectToEdit, newProject.filename().stem().string());

        builder.
            append("success", success).
            append("message", move(message));

        return builder;
    }
}
