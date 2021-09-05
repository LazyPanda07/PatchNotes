#pragma once

#include "headers.h"

#include "Composites/SeparateWindow.h"
#include "Utility/Holders/WindowHolder.h"

#include "Views/BaseView.h"

class Initializer
{
private:
	gui_framework::SeparateWindow* mainWindow;

private:
	std::unique_ptr<::views::BaseView> projectConfigurationView;
	std::unique_ptr<::views::BaseView> patchNotesView;
	std::unique_ptr<::views::BaseView> categoryConfigurationView;
	std::unique_ptr<::views::BaseView> generateHTMLView;
	std::unique_ptr<::views::BaseView> previewPatchNotesView;
	std::unique_ptr<::views::BaseView> deleteProjectConfigurationView;
	std::unique_ptr<::views::BaseView> deleteCategoryView;
	std::unique_ptr<::views::BaseView> deleteElementView;
	std::unique_ptr<::views::BaseView> deleteNoteView;

	std::vector<std::filesystem::path> previewFiles;
	bool isBackgroundImageLoaded;

private:
	void createMenus();

	void registerHotkeys();

	void initBackgroundPatchNotesColor();

	void initBackgroundImage();

private:
	Initializer();

	~Initializer() = default;

public:
	static Initializer& get();

	void createUI();

	void closeCategory();

	void closeProjectConfiguration();

	void closeDeleteConfiguration();

	void closeDeleteCategory();

	void closeDeleteElement();

	void closeDeleteNote();

	void initialize(std::unique_ptr<gui_framework::WindowHolder>& holder);

	void addPreviewFile(const std::filesystem::path& previewFile);

	void removePreviewFiles();

	bool getIsBackgroundImageLoaded() const;
};
