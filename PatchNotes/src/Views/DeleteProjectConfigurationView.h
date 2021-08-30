#pragma once

#include "BaseView.h"

#include "BaseComposites/BaseComposite.h"

namespace views
{
	class DeleteProjectConfigurationView : public BaseView
	{
	private:
		static gui_framework::BaseComposite* createDeleteCategoryDialog(const std::unique_ptr<controllers::BaseController>& controller);

	public:
		DeleteProjectConfigurationView();

		void update(const json::JSONParser& data) override;

		~DeleteProjectConfigurationView() = default;
	};
}
