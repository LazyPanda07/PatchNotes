#pragma once

#include "Views/BaseView.h"

#include "BaseComposites/BaseComposite.h"

namespace views
{
	class DeleteNoteView : public BaseView
	{
	private:
		static gui_framework::BaseComposite* createDeleteNoteDialog(const std::unique_ptr<controllers::BaseController>& controller);

	public:
		DeleteNoteView();

		void update(const json::JSONParser& data) override;

		~DeleteNoteView() = default;
	};
}
