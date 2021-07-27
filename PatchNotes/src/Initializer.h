#pragma once

#include "pch.h"

#include "Composites/SeparateWindow.h"
#include "Utility/Holders/WindowHolder.h"

#include "Views/ProjectConfigurationView.h"
#include "Controllers/ProjectConfigurationController.h"

class Initializer
{
private:
	gui_framework::SeparateWindow* mainWindow;

private:
	std::shared_ptr<controllers::BaseController> projectConfigurationController;
	views::interfaces::IObserver* projectConfigurationViewRawPointer;

private:
	void createMenus();

public:
	Initializer();

	void initialization(std::unique_ptr<gui_framework::WindowHolder>& holder);

	~Initializer() = default;
};
