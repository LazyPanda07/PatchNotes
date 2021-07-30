#pragma once

#include "pch.h"

#include "Composites/SeparateWindow.h"
#include "Utility/Holders/WindowHolder.h"

#include "Views/ProjectConfigurationView.h"
#include "Views/PatchNotesView.h"
#include "Views/CategoryConfigurationView.h"
#include "Views/GenerateHTMLView.h"

#include "Controllers/ProjectConfigurationController.h"
#include "Controllers/PatchNotesController.h"
#include "Controllers/CategoryConfigurationController.h"
#include "Controllers/GenerateHTMLController.h"

class Initializer
{
private:
	gui_framework::SeparateWindow* mainWindow;

private:
	std::shared_ptr<controllers::BaseController> projectConfigurationController;
	views::interfaces::IObserver* projectConfigurationViewRawPointer;

	std::shared_ptr<controllers::BaseController> patchNotesController;

	std::shared_ptr<controllers::BaseController> categoryConfigurationController;
	views::interfaces::IObserver* categoryConfigurationViewRawPointer;

	std::shared_ptr<controllers::GenerateHTMLController> generateHTMLController;
	std::unique_ptr<views::GenerateHTMLView> generateHTMLView;

private:
	void createMenus();

	void createUI();

public:
	Initializer();

	void initialization(std::unique_ptr<gui_framework::WindowHolder>& holder);

	~Initializer() = default;
};
