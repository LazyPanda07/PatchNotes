#pragma once

#include "BaseView.h"

#include "BaseComposites/BaseComposite.h"

namespace views
{
	class DeleteProjectConfigurationView : public BaseView
	{
	public:
		DeleteProjectConfigurationView();

		void update(const json::JSONParser& data) override;

		void onClick(gui_framework::BaseComposite* patchNotesWindow);

		~DeleteProjectConfigurationView() = default;
	};
}
