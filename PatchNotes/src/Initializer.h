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
	std::shared_ptr<views::interfaces::IObserver> projectConfigurationView;

private:
	void createMenus();

public:
	Initializer() = default;

	void initialization(std::unique_ptr<gui_framework::WindowHolder>& holder);

	~Initializer() = default;
};
