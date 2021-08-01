#pragma once

#include "BaseView.h"

#include "pch.h"

#include "BaseComposites/BaseComposite.h"

namespace views
{
	class GenerateHTMLView : public BaseView
	{
	private:
		gui_framework::BaseComposite* mainWindow;

	public:
		GenerateHTMLView(gui_framework::BaseComposite* mainWindow);

		void update(const json::JSONParser& data) override;

		void onClick(gui_framework::BaseComposite* patchNotesWindow);

		~GenerateHTMLView() = default;
	};
}
