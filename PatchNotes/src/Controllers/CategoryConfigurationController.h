#pragma once

#include "BaseController.h"

namespace controllers
{
	class CategoryConfigurationController : public BaseController
	{
	private:
		json::JSONBuilder collectData(gui_framework::BaseComposite* window) const override;

	public:
		CategoryConfigurationController();

		~CategoryConfigurationController() = default;
	};
}
