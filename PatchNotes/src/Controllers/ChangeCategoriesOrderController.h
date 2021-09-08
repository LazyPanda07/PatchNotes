#pragma once

#include "BaseController.h"

namespace controllers
{
	class ChangeCategoriesOrderController : public BaseController
	{
	private:
		json::JSONBuilder collectData(gui_framework::BaseComposite* window) const;

	public:
		ChangeCategoriesOrderController();

		~ChangeCategoriesOrderController() = default;
	};
}
