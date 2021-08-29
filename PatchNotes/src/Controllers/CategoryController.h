#pragma once

#include "BaseController.h"

namespace controllers
{
	class CategoryController : public BaseController
	{
	private:
		json::JSONBuilder collectData(gui_framework::BaseComposite* window) const override;

	public:
		CategoryController();

		~CategoryController() = default;
	};
}
