#pragma once

#include "BaseView.h"
#include "Controllers/BaseController.h"

namespace views
{
	class ProjectConfigurationView : public BaseView
	{
	private:
		static gui_framework::BaseComposite* createConfigurationDialog(const std::shared_ptr<controllers::BaseController>& controller);

	public:
		ProjectConfigurationView(const std::shared_ptr<controllers::BaseController>& controller);

		void update(const json::JSONParser& data) override;

		~ProjectConfigurationView() = default;
	};
}
