#pragma once

#include "BaseController.h"

namespace controllers
{
	class DeleteProjectConfigurationController : public BaseController
	{
	private:
		json::JSONBuilder collectData(gui_framework::BaseComposite* window) const override;

	public:
		DeleteProjectConfigurationController();

		~DeleteProjectConfigurationController() = default;
	};
}
