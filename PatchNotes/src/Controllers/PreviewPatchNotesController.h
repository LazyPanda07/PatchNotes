#pragma once

#include "BaseController.h"

#include "headers.h"

#include "BaseComposites/BaseComposite.h"

namespace controllers
{
	class PreviewPatchNotesController : public BaseController
	{
	private:
		json::JSONBuilder collectData(gui_framework::BaseComposite* window) const override;

	public:
		PreviewPatchNotesController(gui_framework::BaseComposite* mainWindow);

		~PreviewPatchNotesController() = default;
	};
}
