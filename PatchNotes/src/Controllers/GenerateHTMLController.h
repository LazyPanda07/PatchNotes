#pragma once

#include "BaseController.h"

namespace controllers
{
	class GenerateHTMLController : public BaseController
	{
	private:
		json::JSONBuilder collectData(gui_framework::BaseComposite* window) const override;

	public:
		GenerateHTMLController();

		~GenerateHTMLController() = default;
	};
}
