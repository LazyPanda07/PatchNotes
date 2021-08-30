#pragma once

#include "BaseController.h"

namespace controllers
{
	class DeleteCategoryController : public BaseController
	{
	private:
		json::JSONBuilder collectData(gui_framework::BaseComposite* window) const override;

	public:
		DeleteCategoryController();

		~DeleteCategoryController() = default;
	};
}
