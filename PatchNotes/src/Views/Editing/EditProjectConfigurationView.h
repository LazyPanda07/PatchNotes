#pragma once

#include "Views/BaseView.h"

#include "BaseComposites/BaseComposite.h"

namespace views
{
	class EditProjectConfigurationView : public BaseView
	{
	private:
		static gui_framework::BaseComposite* createEditProjectConfigurationDialog(const std::unique_ptr<controllers::BaseController>& controller);

	public:
		EditProjectConfigurationView();

		void update(const json::JSONParser& data) override;

		~EditProjectConfigurationView() = default;
	};
}
