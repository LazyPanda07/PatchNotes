#pragma once

#include "BaseController.h"

#include "Utility/Holders/WindowHolder.h"

namespace controllers
{
	class ChangeLanguageController : public BaseController
	{
	private:
		json::JSONBuilder collectData(gui_framework::BaseComposite* window) const override;

	public:
		ChangeLanguageController(std::unique_ptr<gui_framework::WindowHolder>& mainWindow);

		~ChangeLanguageController() = default;
	};
}
