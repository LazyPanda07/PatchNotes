#pragma once

#include "BaseView.h"
#include "Controllers/BaseController.h"

namespace views
{
	class ChangeCategoriesOrderView : public BaseView
	{
	private:
		static gui_framework::BaseComposite* createChangeCategoriesOrderDialog(const std::unique_ptr<controllers::BaseController>& controller, const std::wstring& projectConfiguration);

	public:
		ChangeCategoriesOrderView(const std::wstring& projectConfiguration);

		void update(const json::JSONParser& data) override;

		~ChangeCategoriesOrderView() = default;
	};
}
