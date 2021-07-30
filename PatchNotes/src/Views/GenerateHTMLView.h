#pragma once

#include "BaseView.h"

#include "pch.h"

#include "Components/ProgressBars/ProgressBar.h"

namespace views
{
	class GenerateHTMLView : public BaseView
	{
	private:
		gui_framework::ProgressBar* updateProgressBar;

	public:
		GenerateHTMLView(const std::shared_ptr<controllers::BaseController>& controller, gui_framework::ProgressBar* updateProgressBar);

		void update(const json::JSONParser& data) override;

		void onClick(gui_framework::BaseComposite* patchNotesWindow);

		~GenerateHTMLView() = default;
	};
}
