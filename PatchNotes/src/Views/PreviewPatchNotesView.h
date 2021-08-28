#pragma once

#include "BaseView.h"

namespace views
{
	class PreviewPatchNotesView : public BaseView
	{
	private:
		gui_framework::BaseComposite* mainWindow;

	public:
		PreviewPatchNotesView(gui_framework::BaseComposite* mainWindow);

		void update(const json::JSONParser& data) override;

		void onClick(gui_framework::BaseComposite* patchNotesWindow);

		~PreviewPatchNotesView() = default;
	};
}
