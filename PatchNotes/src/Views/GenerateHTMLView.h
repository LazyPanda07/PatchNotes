#pragma once

#include "BaseView.h"

namespace views
{
	class GenerateHTMLView : public BaseView
	{
	public:
		GenerateHTMLView(const std::shared_ptr<controllers::BaseController>& controller);

		void update(const json::JSONParser& data) override;

		void onClick(gui_framework::BaseComposite* patchNotesWindow);

		~GenerateHTMLView() = default;
	};
}
