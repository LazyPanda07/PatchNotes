#pragma once

#include "BaseView.h"

#include "Utility/Holders/WindowHolder.h"

namespace views
{
	class ChangeLanguageView : public BaseView
	{
	public:
		ChangeLanguageView(gui_framework::BaseComponent* parent, std::unique_ptr<gui_framework::WindowHolder>& mainWindow);

		void update(const json::JSONParser& data) override;

		void onClick();

		~ChangeLanguageView() = default;
	};
}
