#pragma once

#include "pch.h"

#include "Composites/SeparateWindow.h"
#include "Utility/Holders/WindowHolder.h"

#include "Views/BaseView.h"

class Initializer
{
private:
	gui_framework::SeparateWindow* mainWindow;

private:
	std::unique_ptr<views::BaseView> projectConfigurationView;
	std::unique_ptr<views::BaseView> patchNotesView;
	std::unique_ptr<views::BaseView> categoryConfigurationView;
	std::unique_ptr<views::BaseView> generateHTMLView;

private:
	void createMenus();

	void createUI();

public:
	Initializer();

	void initialization(std::unique_ptr<gui_framework::WindowHolder>& holder);

	~Initializer() = default;
};
