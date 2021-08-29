#pragma once

#include "BaseView.h"
#include "Controllers/BaseController.h"

namespace views
{
	class CategoryView : public BaseView
	{
	private:
		static gui_framework::BaseComposite* createCategoryDialog(const std::unique_ptr<controllers::BaseController>& controller, const std::wstring& projectNameAndVersion);

	public:
		CategoryView(const std::wstring& projectNameAndVersion);

		void update(const json::JSONParser& data) override;

		~CategoryView() = default;
	};
}
