#pragma once

#include <string>

#include "WTextLocalization.h"

namespace globals
{
	inline std::string dataFolder;
    inline std::wstring pathToPatchNotes;
}

namespace command_line
{
    inline constexpr std::wstring_view restart = L"restart";
}

namespace json_settings
{
    inline const std::string language = "language";
    inline const std::string pathToBackgroundImage = "pathToBackgroundImage";
    inline const std::string pathToProjectLogo = "pathToProjectLogo";
}

namespace patch_notes_constants
{
    inline const std::wstring projectName = OUT_PROJECT_NAME + std::wstring(L".exe");

    inline const std::wstring successTitle = localization::WTextLocalization::get()["success"];
    inline const std::wstring errorTitle = localization::WTextLocalization::get()["error"];

	inline const std::string assetsFolder = "assets";

	inline constexpr std::string_view jsonVersionsFolder = "json_versions";

	inline constexpr std::string_view htmlGeneratedFolder = "docs";

	inline const std::string stylesFileName = "styles.css";
}

namespace sizes
{
	inline constexpr uint16_t mainWindowWidth = 1024;
	inline constexpr uint16_t mainWindowHeight = 768;

	inline constexpr uint16_t patchNotesWidth = mainWindowWidth;
	inline constexpr uint16_t patchNotesHeight = mainWindowHeight;
}

namespace patch_notes_localization
{
    inline const std::string createNewConfiguration = "createNewConfiguration";
    inline const std::string createNewCategory = "createNewCategory";
    inline const std::string create= "create";
    inline const std::string preview= "preview";
    inline const std::string generateNotes = "generateNotes";
    inline const std::string changeCategoriesOrder = "changeCategoriesOrder";
    inline const std::string deleteConfiguration = "deleteConfiguration";
    inline const std::string deleteCategory = "deleteCategory";
    inline const std::string deleteElement = "deleteElement";
    inline const std::string deleteNote = "deleteNote";
    inline const std::string deleteButton = "delete";
    inline const std::string editConfiguration = "editConfiguration";
    inline const std::string editCategory = "editCategory";
    inline const std::string editElement = "editElement";
    inline const std::string editNote = "editNote";
    inline const std::string editButton = "edit";
    inline const std::string fieldCantBeEmpty = "fieldCantBeEmpty";
    inline const std::string notes = "notes";
    inline const std::string failedToFindConfiguration = "failedToFindConfiguration";
    inline const std::string failedToFindProject = "failedToFindProject";
    inline const std::string failedToFindCategory = "failedToFindCategory";
    inline const std::string currentProject = "currentProject";
    inline const std::string categoryConfiguration = "categoryConfiguration";
    inline const std::string categoryName = "categoryName";
    inline const std::string add = "add";
    inline const std::string categoryAddedSuccessfully = "categoryAddedSuccessfully";
    inline const std::string categoryAlreadyExists = "categoryAlreadyExists";
    inline const std::string categoryOrderChangedSuccessfully = "categoryOrderChangedSuccessfully";
    inline const std::string categorySuccessfullyDeleted = "categorySuccessfullyDeleted";
    inline const std::string elementSuccessfullyDeleted = "elementSuccessfullyDeleted";
    inline const std::string noteSuccessfullyDeleted = "noteSuccessfullyDeleted";
    inline const std::string configurationSuccessfullyDeleted = "configurationSuccessfullyDeleted";
    inline const std::string failedToDeleteConfiguration = "failedToDeleteConfiguration";
    inline const std::string categoryChanged = "categoryChanged";
    inline const std::string elementChanged = "elementChanged";
    inline const std::string noteChanged = "noteChanged";
    inline const std::string configurationChanged = "configurationChanged";
    inline const std::string fileGeneratedSuccessfully = "fileGeneratedSuccessfully";
    inline const std::string repeatCommandLater = "repeatCommandLater";
    inline const std::string failedToGenerateNotes = "failedToGenerateNotes";
    inline const std::string backgroundNotLoadedYet = "backgroundNotLoadedYet";
    inline const std::string faviconNotLoadedYet = "faviconNotLoadedYet";
    inline const std::string elementSuccessfullyAdded = "elementSuccessfullyAdded";
    inline const std::string elementAlreadyExists = "elementAlreadyExists";
    inline const std::string dataForPreviewSuccessfullyGenerated = "dataForPreviewSuccessfullyGenerated";
    inline const std::string failedToGeneratePreview = "failedToGeneratePreview";
    inline const std::string fileAlreadyExists = "fileAlreadyExists";
    inline const std::string configurationSuccessfullyAdded = "configurationSuccessfullyAdded";
    inline const std::string newCategoryName = "newCategoryName";
    inline const std::string newElementName = "newElementName";
    inline const std::string newNoteName = "newNoteName";
    inline const std::string newConfigurationName = "newConfigurationName";
    inline const std::string newVersion= "newVersion";
    inline const std::string element= "element";
    inline const std::string projectConfiguration = "projectConfiguration";
    inline const std::string projectName = "projectName";
    inline const std::string projectVersion = "projectVersion";
}

namespace patch_notes_constants
{
	inline std::string styles = R"(html {
    font-family: Calibri;
}

td {
    width: 20%;
}

.patch-notes {
    background-image: url([0]);
    background-size: 100%;
}

.version {
    margin-bottom: 4%;
    text-align: center;
}

.patch-notes-container {
    margin-top: 0.5%;
    margin-bottom: 0.5%;
    margin-left: 30%;
    margin-right: 30%;
    align-items: center;
    background-color: rgba([1]);
    border-radius: 5px;
}

.category {
    margin-left: 10px;
    margin-bottom: 10px;
    font-size: xx-large;
}

.element {
    font-size: x-large;
    margin-bottom: 7px;
    margin-left: 20px;
}

.note {
    margin-left: 20px;
    font-size: large;
    color: rgba(0, 0, 0, 0.7);
}

.project-logo {
    width: 64px;
    height: 64px;
    margin-top: 18px;
    margin-left: 40px;
    float: left;
}

.title {
    color: white;
    margin-left: 20%;
    font-style: italic;
    padding-top: 30.5px;
    float: left;
}

.title-container {
    margin-top: 1%;
    background-color: rgb(16, 28, 36);
    font-size: xx-large;
    margin-left: 20%;
    margin-right: 20%;
    height: 100px;
}

.link-to-patch {
    background-color: black;
    color: white;
    text-decoration: none;
    display: inline-block;
    cursor: pointer;
    border: 1px solid transparent;
    -webkit-user-select: none;
    -moz-user-select: none;
    -ms-user-select: none;
    width: 100%;
    user-select: none;
    text-align: center;
    padding-top: 20%;
    padding-bottom: 20%;
}

.links-container {
    margin-top: 5%;
    margin-left: 25%;
    margin-right: 25%;
}
)";
}
