#pragma once

#include "headers.h"

#include "Composites/SeparateWindow.h"
#include "Utility/Holders/WindowHolder.h"

#include "Views/BaseView.h"

class Initializer
{
private:
	enum class hotkeyTypes
	{
		none,
		editType,
		deleteType
	};

private:
	gui_framework::SeparateWindow* mainWindow;

private:
	std::unique_ptr<::views::BaseView> projectConfigurationView;
	std::unique_ptr<::views::BaseView> patchNotesView;
	std::unique_ptr<::views::BaseView> changeLanguageView;
	std::unique_ptr<::views::BaseView> categoryConfigurationView;
	std::unique_ptr<::views::BaseView> generateHTMLView;
	std::unique_ptr<::views::BaseView> previewPatchNotesView;
	std::unique_ptr<::views::BaseView> changeCategoriesOrderView;

	std::unique_ptr<::views::BaseView> deleteProjectConfigurationView;
	std::unique_ptr<::views::BaseView> deleteCategoryView;
	std::unique_ptr<::views::BaseView> deleteElementView;
	std::unique_ptr<::views::BaseView> deleteNoteView;

	std::unique_ptr<::views::BaseView> editProjectConfigurationView;
	std::unique_ptr<::views::BaseView> editCategoryView;
	std::unique_ptr<::views::BaseView> editElementView;
	std::unique_ptr<::views::BaseView> editNoteView;

	std::vector<std::filesystem::path> previewFiles;
	bool isBackgroundImageLoaded;
	bool isFaviconLoaded;
	std::string favicon;
	hotkeyTypes currentHotkeyType;

private:
	void initDeletingMenuItem(std::unique_ptr<gui_framework::Menu>& menu);

	void initEditingMenuItem(std::unique_ptr<gui_framework::Menu>& menu);

	void createMenus(std::unique_ptr<gui_framework::WindowHolder>& holder);

	void registerHotkeys();

	void initBackgroundPatchNotesColor();

	void initBackgroundImage();

	void initFavicon();

private:
	void createProjectConfiguration();

	void createCategory();

	void changeCategoriesOrder();

	void changeLanguage(std::unique_ptr<gui_framework::WindowHolder>& holder);

#pragma region Deleting
	void deleteProjectConfiguration();

	void deleteCategory();

	void deleteElement();

	void deleteNote();
#pragma endregion

#pragma region Editing
	void editProjectConfiguration();

	void editCategory();

	void editElement();

	void editNote();
#pragma endregion

private:
	Initializer();

	~Initializer() = default;

public:
	static Initializer& get();

	void createUI();

	void closeCategory();

	void closeProjectConfiguration();

	void closeChangeCategoriesOrder();

#pragma region Deleting
	void closeDeleteConfiguration();

	void closeDeleteCategory();

	void closeDeleteElement();

	void closeDeleteNote();
#pragma endregion

#pragma region Editing
	void closeEditProjectConfiguration();

	void closeEditCategory();

	void closeEditElement();

	void closeEditNote();
#pragma endregion

	void initialize(std::unique_ptr<gui_framework::WindowHolder>& holder);

	void addPreviewFile(const std::filesystem::path& previewFile);

	void removePreviewFiles();

	void generateHTML();

	void previewPatchNotes();

	bool getIsBackgroundImageLoaded() const;

	bool getIsFaviconLoaded() const;

	const std::string& getFavicon() const;
};
