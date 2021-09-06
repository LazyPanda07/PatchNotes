#include "EditProjectConfigurationModel.h"

#include "PatchNotesUtility.h"
#include "PatchNotesConstants.h"

using namespace std;

namespace models
{
    json::JSONBuilder EditProjectConfigurationModel::processData(const json::JSONParser& data)
    {
        uint32_t codepage = utility::getCodepage();
        json::JSONBuilder builder(codepage);
        const string& projectToEdit = json::utility::fromUTF8JSON(data.getString("projectToEdit"), codepage);
        filesystem::path pathToProject = filesystem::path(globals::dataFolder) /= projectToEdit + ".json";
        const string& newProjectName = json::utility::fromUTF8JSON(data.getString("newProjectName"), codepage);
        const string& newProjectVersion = json::utility::fromUTF8JSON( data.getString("newProjectVersion"), codepage);
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

        message = format(R"(Конфигурация \"{}\" была успешно переименована в \"{}\")", projectToEdit, newProject.filename().stem().string());

        builder.
            append("success", success).
            append("message", move(message));

        return builder;
    }
}
