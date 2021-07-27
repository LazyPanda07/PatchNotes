#pragma once

#include "BaseView.h"
#include "Controllers/BaseController.h"

namespace views
{
	class ProjectConfigurationView : public BaseView
	{
	private:
		static std::unique_ptr<gui_framework::BaseComposite> createConfigurationDialog();

	public:
		ProjectConfigurationView(const std::shared_ptr<controllers::BaseController>& controller);

		void update(const json::JSONParser& data) override;

		~ProjectConfigurationView();
	};
}

CREATE_DEFAULT_WINDOW_FUNCTION(projectConfiguration)
