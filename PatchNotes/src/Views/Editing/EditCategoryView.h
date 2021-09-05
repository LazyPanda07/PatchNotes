#pragma once

#include "Views/BaseView.h"

namespace views
{
	class EditCategoryView : public BaseView
	{
	private:
		static gui_framework::BaseComposite* createEditCategoryDialog(const std::unique_ptr<controllers::BaseController>& controller);

	public:
		EditCategoryView();

		void update(const json::JSONParser& data) override;

		~EditCategoryView() = default;
	};
}
