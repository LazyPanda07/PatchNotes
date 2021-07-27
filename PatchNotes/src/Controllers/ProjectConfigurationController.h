#pragma once

#include "BaseController.h"

namespace controllers
{
	class ProjectConfigurationController : public BaseController
	{
	private:
		json::JSONBuilder collectData(gui_framework::BaseComposite* window) const override;

	public:
		ProjectConfigurationController();

		~ProjectConfigurationController() = default;
	};
}
