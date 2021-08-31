#pragma once

#include "BaseController.h"

namespace controllers
{
	class DeleteNoteController : public BaseController
	{
	private:
		json::JSONBuilder collectData(gui_framework::BaseComposite* window) const override;

	public:
		DeleteNoteController();

		~DeleteNoteController() = default;
	};
}
