#pragma once

#include "Controllers/BaseController.h"

namespace controllers
{
	class EditProjectConfigurationController : public BaseController
	{
	private:
		json::JSONBuilder collectData(gui_framework::BaseComposite* window) const override;

	public:
		EditProjectConfigurationController();

		~EditProjectConfigurationController() = default;
	};
}
