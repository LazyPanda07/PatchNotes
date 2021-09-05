#pragma once

#include "Controllers/BaseController.h"

namespace controllers
{
	class EditCategoryController : public BaseController
	{
	private:
		json::JSONBuilder collectData(gui_framework::BaseComposite* window) const override;

	public:
		EditCategoryController();

		~EditCategoryController() = default;
	};
}
