#pragma once

#include "BaseView.h"

#include "BaseComposites/BaseComposite.h"

namespace views
{
	class DeleteCategoryView : public BaseView
	{
	private:
		static gui_framework::BaseComposite* createDeleteCategoryDialog(const std::unique_ptr<controllers::BaseController>& controller);

	public:
		DeleteCategoryView();

		void update(const json::JSONParser& data) override;

		~DeleteCategoryView() = default;
	};
}
