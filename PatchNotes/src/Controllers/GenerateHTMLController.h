#pragma once

#include "BaseController.h"

#include "pch.h"

#include "Components/ProgressBars/ProgressBar.h"

namespace controllers
{
	class GenerateHTMLController : public BaseController
	{
	private:
		json::JSONBuilder collectData(gui_framework::BaseComposite* window) const override;

	public:
		GenerateHTMLController(gui_framework::ProgressBar* updateProgressBar);

		~GenerateHTMLController() = default;
	};
}
