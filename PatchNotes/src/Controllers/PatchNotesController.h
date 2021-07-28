#pragma once

#include "BaseController.h"

namespace controllers
{
	class PatchNotesController : public BaseController
	{
	private:
		json::JSONBuilder collectData(gui_framework::BaseComposite* window) const override;

	public:
		PatchNotesController();

		~PatchNotesController() = default;
	};
}
