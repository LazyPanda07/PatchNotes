#pragma once

#include <string>

namespace globals
{
	inline std::string dataFolder;
}

namespace patch_notes_constants
{
	inline const std::wstring successTitle = L"Успех";
	inline const std::wstring errorTitle = L"Ошибка";

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

.title {
    color: white;
    margin-left: 20%;
    font-style: italic;
    padding-top: 30.5px;
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
