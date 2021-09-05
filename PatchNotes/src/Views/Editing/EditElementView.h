#pragma once

#include "Views/BaseView.h"

#include "BaseComposites/BaseComposite.h"

namespace views
{
	class EditElementView : public BaseView
	{
	private:
		static gui_framework::BaseComposite* createEditElementDialog(const std::unique_ptr<controllers::BaseController>& controller);

	public:
		EditElementView();

		void update(const json::JSONParser& data) override;

		~EditElementView() = default;
	};
}
