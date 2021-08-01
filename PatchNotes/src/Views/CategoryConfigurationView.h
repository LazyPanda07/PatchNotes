#pragma once

#include "BaseView.h"
#include "Controllers/BaseController.h"

namespace views
{
	class CategoryConfigurationView : public BaseView
	{
	private:
		static gui_framework::BaseComposite* createCategoryDialog(const std::unique_ptr<controllers::BaseController>& controller, const std::wstring& projectNameAndVersion);

	private:
		std::unique_ptr<controllers::BaseController>& patchNotesController;

	public:
		CategoryConfigurationView(const std::wstring& projectNameAndVersion, std::unique_ptr<controllers::BaseController>& patchNotesController);

		void update(const json::JSONParser& data) override;

		~CategoryConfigurationView() = default;
	};
}
