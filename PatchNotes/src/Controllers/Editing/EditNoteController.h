#pragma once

#include "Controllers/BaseController.h"

namespace controllers
{
	class EditNoteController : public BaseController
	{
	private:
		json::JSONBuilder collectData(gui_framework::BaseComposite* window) const override;

	public:
		EditNoteController();

		~EditNoteController() = default;
	};
}
