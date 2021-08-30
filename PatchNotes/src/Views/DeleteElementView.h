#pragma once

#include "BaseView.h"

#include "BaseComposites/BaseComposite.h"

namespace views
{
	class DeleteElementView : public BaseView
	{
	private:
		static gui_framework::BaseComposite* createDeleteElementDialog(const std::unique_ptr<controllers::BaseController>& controller);

	public:
		DeleteElementView();

		void update(const json::JSONParser& data) override;

		~DeleteElementView() = default;
	};
}
