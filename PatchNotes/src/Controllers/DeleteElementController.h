#pragma once

#include "BaseController.h"

namespace controllers
{
	class DeleteElementController : public BaseController
	{
	private:
		json::JSONBuilder collectData(gui_framework::BaseComposite* window) const override;

	public:
		DeleteElementController();

		~DeleteElementController() = default;
	};
}
