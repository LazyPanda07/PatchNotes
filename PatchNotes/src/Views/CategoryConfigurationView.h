#pragma once

#include "BaseView.h"
#include "Controllers/BaseController.h"

namespace views
{
	class CategoryConfigurationView : public BaseView
	{
	private:
		static gui_framework::BaseComposite* createCategoryDialog(const std::shared_ptr<controllers::BaseController>& controller, const std::wstring& projectNameAndVersion);

	public:
		CategoryConfigurationView(const std::shared_ptr<controllers::BaseController>& controller, const std::wstring& projectNameAndVersion);

		void update(const json::JSONParser& data) override;

		~CategoryConfigurationView() = default;
	};
}
