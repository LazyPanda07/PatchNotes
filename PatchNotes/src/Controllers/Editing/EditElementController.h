#pragma once

#include "Controllers/BaseController.h"

namespace controllers
{
	class EditElementController : public BaseController
	{
	private:
		json::JSONBuilder collectData(gui_framework::BaseComposite* window) const override;

	public:
		EditElementController();
		
		~EditElementController() = default;
	};
}
