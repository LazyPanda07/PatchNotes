#pragma once

#include "BaseController.h"

#include "pch.h"

#include "BaseComposites/BaseComposite.h"

namespace controllers
{
	class GenerateHTMLController : public BaseController
	{
	private:
		json::JSONBuilder collectData(gui_framework::BaseComposite* window) const override;

	public:
		GenerateHTMLController(gui_framework::BaseComposite* mainWindow);

		~GenerateHTMLController() = default;
	};
}
