#pragma once

#include "BaseModel.h"

#include "headers.h"

#include "BaseComposites/BaseComposite.h"

namespace models
{
	class PreviewPatchNotesModel : public BaseModel
	{
	private:
		gui_framework::BaseComposite* mainWindow;

	private:
		json::JSONBuilder processData(const json::JSONParser& data) override;

	public:
		PreviewPatchNotesModel(gui_framework::BaseComposite* mainWindow);

		~PreviewPatchNotesModel() = default;
	};
}
