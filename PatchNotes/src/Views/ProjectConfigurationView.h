#pragma once

#include "BaseView.h"
#include "Controllers/BaseController.h"

namespace views
{
	class ProjectConfigurationView : public BaseView
	{
	private:
		static gui_framework::BaseComposite* createConfigurationDialog(const std::unique_ptr<controllers::BaseController>& controller);

	private:
		std::unique_ptr<controllers::BaseController>& patchNotesController;

	public:
		ProjectConfigurationView(std::unique_ptr<controllers::BaseController>& patchNotesController);

		void update(const json::JSONParser& data) override;

		~ProjectConfigurationView() = default;
	};
}
